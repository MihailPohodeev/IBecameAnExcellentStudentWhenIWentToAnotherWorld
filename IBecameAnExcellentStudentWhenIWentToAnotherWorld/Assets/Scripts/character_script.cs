using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class character_script : MonoBehaviour
{
    public string CharacterName = "";
    public dialog_panel DP;
    public Animator anim;
    // Start is called before the first frame update
    void Start()
    {
        ;
    }

    // Update is called once per frame
    void Update()
    {
        if (DP.txt_split.isThinking) anim.SetBool("isThinking", true);
        else{
            anim.SetBool("isThinking", false);
            anim.SetBool("isSpeak", DP.Speaking());
        }

        if (DP.txt_split.character_name == CharacterName){
             anim.SetBool("isActive", true);
        }
        else{
            anim.SetBool("isActive", false);
        }
    }
}
