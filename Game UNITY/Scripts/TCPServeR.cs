using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;
using Newtonsoft.Json;



public class Package
{

    public bool Move_up { get; set; }
    public bool Move_down { get; set; }
    public bool Move_right { get; set; }
    public bool Move_left { get; set; }
    public bool Shoot { get; set; }
    public bool Reset { get; set; }
    public string Message { get; set; }

  
}

public class TCPServeR : MonoBehaviour
{



    Package package = new Package();
  //  #region private members 	
    /// <summary> 	
    /// TCPListener to listen for incomming TCP connection 	
    /// requests. 	
    /// </summary> 	
    private TcpListener tcpListener;
    /// <summary> 
    /// Background thread for TcpServer workload. 	
    /// </summary> 	
    private Thread tcpListenerThread;
    /// <summary> 	
    /// Create handle to connected tcp client. 	
    /// </summary> 	
    private TcpClient connectedTcpClient;
    public string currentMessage = null;
    //  #endregion
    public double[] doubleArray = new double[10];
    // Use this for initialization
    void Start()
    {
        // Start TcpServer background thread 		
        tcpListenerThread = new Thread(new ThreadStart(ListenForIncommingRequests));
        tcpListenerThread.IsBackground = true;
        tcpListenerThread.Start();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            SendMessage();
        }
    }

   
    /// <summary> 	
    /// Runs in background TcpServerThread; Handles incomming TcpClient requests 	
    /// </summary> 	
    private void ListenForIncommingRequests()
    {
        try
        {
            // Create listener on localhost port 10000 			
            tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), 10000);
            tcpListener.Start();
            Debug.Log("Server is listening");
            Byte[] bytes = new Byte[1024];
            while (true)
            {
                using (connectedTcpClient = tcpListener.AcceptTcpClient())
                
                    // Get a stream object for reading 					
                    using (NetworkStream stream = connectedTcpClient.GetStream())
                     {
                    int length = 0;
                    while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {

                        //array to store data from buffer
                        byte[] incommingData = new byte[2048];
                        Array.Copy(bytes, 0, incommingData, 0, length);

                        //decode received message to ASCII
                        string clientMessage = Encoding.ASCII.GetString(incommingData);
                       
                        //Convert received string to Package type (JSON FORMAT), now i can refer to it's attributes
                        Package deserializedPackage = JsonConvert.DeserializeObject<Package>(clientMessage);

                        deserializedPackage.Message = bytes[1].ToString();
                        //If i would like to print Json format, i need to Serialize it.
                        Debug.Log(JsonConvert.SerializeObject(deserializedPackage));




                    }
                }
                }
                
            }
        
        catch (SocketException socketException)
        {
            Debug.Log("SocketException " + socketException.ToString());
        }
        finally
        {
            Debug.Log("Player has disconnected");
        }
    }
    /// <summary> 	
    /// Send message to client using socket connection. 	
    /// </summary> 	
    private void SendMessage()
    {
        if (connectedTcpClient == null)
        {
            return;
        }

        try
        {
            // Get a stream object for writing. 			
            NetworkStream stream = connectedTcpClient.GetStream();
            if (stream.CanWrite)
            {
                string serverMessage = "This is a message from your server.";
                // Convert string message to byte array.                 
                byte[] serverMessageAsByteArray = Encoding.ASCII.GetBytes(serverMessage);
                // Write byte array to socketConnection stream.               
                stream.Write(serverMessageAsByteArray, 0, serverMessageAsByteArray.Length);
                Debug.Log("Server sent his message - should be received by client");
            }
        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }
    public string GetCurrentMessage()
    {
        return currentMessage;
    }
    public void SetCurrentMessage(string message)
    {
        currentMessage = message;
    }
}