using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class text_spliter : MonoBehaviour
{
    private StreamReader TEXTstream; // текстовый поток.
    public string text = ""; // строка для хранения всего сценария.
    public string current_speech = "", character_name = ""; // текущая речь и имя текущего персонажа.
    public List<string> characters = new List<string>(); // массив действующих персонажей.
    private bool isNameReading = false; // переменная для считывания имени текущего персонажа.
    private bool break_bool = false; // переменная для остановки считывания строки.
    public bool speakind = false; // булевая переменная, описывающая текущее действие персонажа.
    public bool comment = false; // булевая переменная для считывания комментариев.
    private int dialogNumber = 0;
    private float time = 0; // переменная времени для последовательного выведения текста.
    public float limit_time = 0.1f; // переменная предельного времени для вывода каждого отдельного символа.
    public bool isThinking = false;
    
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


    // подсчёт количества действующих персонажей в диалоге.
    public void CountPersons(int dialNUM){

        string nm = "", dialogNumberString = "";
        bool isReadNumber = false, isRead = false;

        for(int i = 0; i < text.Length; i++){

            if (text[i] == '{') comment = true;
            else if (text[i] == '}') comment = false;
            if (comment) continue;

            if (isRead){
                if (text[i] == '>'){
                        isNameReading = false;
                    }
                if(isNameReading){
                    nm += text[i];
                }
                if (text[i] == '<'){
                    isNameReading = true;
                    if ((nm != "") && !(characters.Contains(nm))) characters.Add(nm);
                    nm = "";
                }
            }

            if (text[i] == '[') {
                dialogNumberString = "";
                isReadNumber = true;
            }
            if (isReadNumber) {
                dialogNumberString += text[i];
            }
            if (text[i] == ']') {
                dialogNumberString = dialogNumberString.Trim(new char[] {'[', ']'});
                if (int.Parse(dialogNumberString) == dialNUM) isRead = true;
                else isRead = false;
                isReadNumber = false;
            }
        }
    }

    // выделение текущей речи и имени персонажа
    public void TextSplit(int dialogNUM, ref int position){

        bool isReadingDialogNumber = false;
        string dialogNumberString = "";
        

        for(int i = position; i < text.Length; i++){
            
            if (text[i] == '{') comment = true;
            else if (text[i] == '}') comment = false;
            if (comment) continue;

            if (isReadingDialogNumber){
                dialogNumberString += text[i];
            }

            if (text[i] == '[') {
                isReadingDialogNumber = true;
                dialogNumberString = "";
            }
            if (text[i] == ']') {
                isReadingDialogNumber = false;
                dialogNumberString = dialogNumberString.Trim(new char[] {'[', ']'});
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
                        if (current_speech.Contains('@')){
                            isThinking = true;
                            current_speech = current_speech.Replace("@", "");
                        }
                        else {
                            current_speech = '-' + current_speech;
                            isThinking = false;
                        }
                        current_speech = current_speech.Trim(new char[] {'{', '}', '\n'});
                        Debug.Log(current_speech);
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
        if (time >= limit_time){
            time = 0;
            ind++;
        } else time += Time.deltaTime;
        return str;
    }
}
