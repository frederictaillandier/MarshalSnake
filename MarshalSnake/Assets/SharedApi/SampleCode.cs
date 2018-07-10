using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using AOT;
using System;

public class SampleCode : MonoBehaviour
{
    static IntPtr nativeLibraryPtr;

    delegate int GetGlobal();
    delegate void RunThread();
    delegate void KillThread();
    delegate void InitCore(System.Action<int, string> _action, System.Action<int, Vector3> _action2, System.Action<string> _log);
    delegate void UpdateMainThread();
    delegate void OnKeyUp(KeyCode k);
    delegate void OnKeyDown(KeyCode k);

    Dictionary<int, BehaviourItem> m_ItemDictionary = new Dictionary<int, BehaviourItem>();

    public List<BehaviourItem> m_Samples;
    static SampleCode m_Instance = null;

    static BehaviourItem GetSample(string type)
    {
        for (int i = 0; i < m_Instance.m_Samples.Count; ++i)
        {
            if (type == m_Instance.m_Samples[i].Type)
            {
                return m_Instance.m_Samples[i];
            }
        }
        return m_Instance.m_Samples[0];
    }


    void Awake()
    {
        m_Instance = this;
        if (nativeLibraryPtr != IntPtr.Zero) return;

        nativeLibraryPtr = Native.LoadLibrary("MarshalSnakeCore.dll");
        if (nativeLibraryPtr == IntPtr.Zero)
        {
            Debug.LogError("Failed to load native library");
        }
    }

    // Use this for initialization
    void Start()
    {
        Native.Invoke<InitCore>(nativeLibraryPtr, OnCreateObject, OnPositionChange, Log);
        Native.Invoke<RunThread>(nativeLibraryPtr);
    }

    // Update is called once per frame
    void Update()
    {
        Native.Invoke<UpdateMainThread>(nativeLibraryPtr);
    }

    [MonoPInvokeCallback(typeof(System.Action<int, string>))]
    static void OnCreateObject(int UID, string typeName)
    {
        BehaviourItem b = Instantiate<BehaviourItem>(GetSample(typeName)) as BehaviourItem;

        b.Init(UID);
        m_Instance.m_ItemDictionary[UID] = b;
    }

    [MonoPInvokeCallback(typeof(System.Action<int, Vector3>))]
    static void OnPositionChange(int UID, Vector3 position)
    {
        if (m_Instance.m_ItemDictionary != null && m_Instance.m_ItemDictionary.ContainsKey(UID))
        {
            m_Instance.m_ItemDictionary[UID].transform.position = position;
         }
    }

    void OnGUI()
    {
        if (Event.current.type == EventType.KeyDown)
        {
            if (Input.GetKeyDown(Event.current.keyCode))
            {
                Native.Invoke<OnKeyDown>(nativeLibraryPtr, Event.current.keyCode);
            }
        }
        if (Event.current.type == EventType.KeyUp)
        {
            Native.Invoke<OnKeyUp>(nativeLibraryPtr, Event.current.keyCode);
        }
    }

    private void Log(string log)
    {
        Debug.Log(log);
    }

    void OnApplicationQuit()
    {
        Native.Invoke<KillThread>(nativeLibraryPtr);
        if (nativeLibraryPtr == IntPtr.Zero) return;
        if (Native.FreeLibrary(nativeLibraryPtr))
        {
            Debug.Log("Gameplay library successfully unloaded.");
        }
        else
        {
            Debug.LogError("Gameplay library could not be unloaded.");
        }
    }
}
