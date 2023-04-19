using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneSwitch : MonoBehaviour
{
    public int gameover;


    private void OnTriggerEnter2D(Collider2D other)
    {
        print("Trigger Entered");

        if(other.tag == "Player")
        {
            print("Switching Scene to" + gameover);
            SceneManager.LoadScene(gameover, LoadSceneMode.Single);
        }
    }

}
