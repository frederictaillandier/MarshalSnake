using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BehaviourItem : MonoBehaviour
{
    int m_UID;
    [SerializeField]
    string m_Type = "default";

    public int UID
    {
        get { return m_UID; }
    }

    public string Type
    {
        get { return m_Type; }
    }


    public void Init(int UID)
    {
        m_UID = UID;
        transform.name = "UID_" + UID.ToString();
    }

    public void SetPosition(Vector3 position)
    {
        transform.position = position;
        Debug.Log(UID);
    }
}
