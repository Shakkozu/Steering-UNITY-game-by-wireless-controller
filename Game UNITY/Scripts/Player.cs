using System;
using System.Collections;

using UnityEngine;
using UnityEngine.Networking;

public class Player : MonoBehaviour
{
    [SerializeField] float moveSpeed = 10f;
    [SerializeField] float padding; //TODO REMOVE
    [SerializeField] GameObject laserPrefab;
    [SerializeField] float projectileSpeed = 10f;
  //  [SerializeField] Int32 port = 7777;

    float xMin;
    float xMax;
    float yMin;
    float yMax;
    

    // Start is called before the first frame update
    void Start()
    {
        SetUpMoveBoundaries();
        StartCoroutine(PrintAndWait());
    }

    // Update is called once per frame
    void Update()
    {
      //  if (!isLocalPlayer) return;
        Move();
        Fire();
    }
    IEnumerator PrintAndWait()
    {
        Debug.Log("first message");
        yield return new WaitForSeconds(3);
        Debug.Log("second");
    }
    private void Fire()
    {
        if (Input.GetButtonDown("Fire1"))
        {
            GameObject laser = 
                Instantiate(laserPrefab, transform.position, Quaternion.identity) 
                as GameObject;
            laser.GetComponent<Rigidbody2D>().velocity = new Vector2(0, projectileSpeed);
            //Quaternion.identity = no rotation
            Destroy(laser, 3f);
        }
    }

    private void Move()
    {
        var deltaX = Input.GetAxis("Horizontal") * Time.deltaTime * moveSpeed; //now move ratio is independent from frames per second on user's computer
        var deltaY = Input.GetAxis("Vertical") * Time.deltaTime * moveSpeed;

        var newXPos = Mathf.Clamp(transform.position.x + deltaX,xMin+padding,xMax-padding);
        var newYPos = Mathf.Clamp(transform.position.y + deltaY,yMin+.5f,yMax/6);
        transform.position = new Vector2(newXPos, newYPos);
    }
    private void SetUpMoveBoundaries()
    {
        Camera gameCamera = Camera.main;
        xMin = gameCamera.ViewportToWorldPoint(new Vector3(0, 0, 0)).x;
        xMax = gameCamera.ViewportToWorldPoint(new Vector3(1, 0, 0)).x;

        yMin = gameCamera.ViewportToWorldPoint(new Vector3(0, 0, 0)).y;
        yMax = gameCamera.ViewportToWorldPoint(new Vector3(0, 1, 0)).y;
    }

}
