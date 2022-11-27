using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class text_spliter : MonoBehaviour
{
    private StreamReader TEXTstream; // текстовый поток.
    public string text = ""; // строка для хранения всего сценария.
    public string current_speech = "", character_name = ""; // текущая речь и имя текущего персонажа.
    private bool isNameReading = false; // переменная для считывания имени текущего персонажа.
    private bool break_bool = false; // переменная для остановки считывания строки.
    private int dialogNumber = 0;
    void Start()
    {
        // чтение из файла
        try{
            StreamReader TEXTstream = new StreamReader("Assets/Scripts/text.txt");
            text = TEXTstream.ReadToEnd();
        }
        catch{
            Debug.Log("Не получилось, не фартануло!");
        }
    }

    public void CountPersons(){
        ;
    }

    // выделение текущей речи и имени персонажа
    public void TextSplit(int dialogNUM, ref int position){

        bool isReadingDialogNumber = false;
        string dialogNumberString = "";
        

        for(int i = position; i < text.Length; i++){
            
            if (isReadingDialogNumber){
                dialogNumberString += text[i];
            }

            if (text[i] == '(') {
                isReadingDialogNumber = true;
                dialogNumberString = "";
            }
            if (text[i] == ')') {
                isReadingDialogNumber = false;
                dialogNumberString = dialogNumberString.Trim(new char[] {'(', ')'});
                dialogNumber = int.Parse(dialogNumberString);
            }


            
            if ((dialogNUM == dialogNumber) && (!isReadingDialogNumber)){
                if(!isNameReading){
                    current_speech += text[i];
                }

                if (text[i] == '>'){
                    isNameReading = false;
                    current_speech = "";
                }
                if(isNameReading){
                    character_name += text[i];
                }
                if (text[i] == '<'){
                    if (break_bool){
                        break_bool = false;
                        position = i;
                        current_speech = current_speech.Trim(new char[] {'{', '}', ' '});
                        break;
                    }
                    isNameReading = true;
                    character_name = "";
                    break_bool = true;
                }
            }
        }
    }

    public string PrintTextAnimation(string str, ref int ind){
        str = str.Remove(ind);
        ind++;
        return str;
    }
}
