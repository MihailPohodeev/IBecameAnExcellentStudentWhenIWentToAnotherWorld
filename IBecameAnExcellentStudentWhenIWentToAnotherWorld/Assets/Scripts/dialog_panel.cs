using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class dialog_panel : MonoBehaviour
{

    public GameObject textBar;
    public GameObject nameBar;
    public text_spliter txt_split;
    public int current_position = 0;
    private bool isAnimation = false;
    private int speech_pos = 0, name_pos  = 0;

    void Start()
    {
        textBar.GetComponent<Text>().text = "";
        nameBar.GetComponent<Text>().text = ".";
    }


    void Update()
    {
        if (Input.GetMouseButtonDown(0)){
            if(!isAnimation){
                isAnimation = true;
                speech_pos = 0;
                txt_split.TextSplit(1, ref current_position);
                nameBar.GetComponent<Text>().text = txt_split.character_name;
            }
        }
        if (isAnimation){
            if(speech_pos < txt_split.current_speech.Length){
                textBar.GetComponent<Text>().text = '-' + txt_split.PrintTextAnimation(txt_split.current_speech, ref speech_pos);
            } else isAnimation = false;
        }
    }
}
