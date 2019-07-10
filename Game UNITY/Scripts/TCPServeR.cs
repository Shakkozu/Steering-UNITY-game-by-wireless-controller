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
    //  < private members >

    //JSON format package that keeps information about current move,status,etc.
    Package serverPackage = new Package();
    // TCPListener to listen for incomming TCP connection 	
    // requests. 	
    private TcpListener tcpListener;
    // Background thread for TcpServer workload. 	
    private Thread tcpListenerThread;	
    // Create handle to connected tcp client. 	
    private TcpClient connectedTcpClient;
    //
    int length = 0;
     

    //#Functions (UNITY)
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
    //<Class Functions>
   
    // Runs in background TcpServerThread; Handles incomming TcpClient requests 	
    private void ListenForIncommingRequests()
    {
        try
        {
            // Create listener on localhost port 10000 		
            tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), 10000);
            tcpListener.Start();
            Debug.Log("Server is listening");
            Byte[] bytes = new Byte[512];
            while (true)
            {
                //Accept connection requests
                using (connectedTcpClient = tcpListener.AcceptTcpClient())
                    // Get a stream object for reading 					
                    using (NetworkStream stream = connectedTcpClient.GetStream())
                     {
                    
                        while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                        {

                            //array to store data from buffer
                            byte[] incommingData = new byte[512];
                            Array.Copy(bytes, 0, incommingData, 0, length);

                            //decode received message to ASCII
                            string clientMessage = Encoding.ASCII.GetString(incommingData);

                            //Convert received string to Package type (JSON FORMAT), now i can refer to it's attributes
                            try
                            {
                                Package deserializedPackage = JsonConvert.DeserializeObject<Package>(clientMessage);
                                serverPackage = deserializedPackage;
                                //I need to serialize Json format to print it as string
                                Debug.Log(JsonConvert.SerializeObject(deserializedPackage));
                            }
                            catch
                            {
                                Debug.Log("Utracono informacje!");
                                byte[] tmp = new byte[512];
                                incommingData.Equals(tmp);
                            }
                       
                        }
                }
                //Exiting using statement brackets means that connection was lost, (stream closed)
                Debug.Log("Connection Lost!");
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
    ///
   /* TO REFACTORIZE
    * 
    * private Package DecodePackage(string message)
    {
        return JsonConvert.DeserializeObject<Package>(message);
    }
    private string CodePackage(Package pack)
    {
        return JsonConvert.SerializeObject(pack);
    }
    private void RetreiveMessage(ref NetworkStream stream, ref int length, ref Byte[] bytes)
    {
        byte[] incommingData = new byte[512];
        Array.Copy(bytes, 0, incommingData, 0, length);

        //decode received message to ASCII
        string clientMessage = Encoding.ASCII.GetString(incommingData);

        //Convert received string to Package type (JSON FORMAT), now i can refer to it's attributes
        try
        {
            serverPackage = DecodePackage(clientMessage);

            //I need to serialize Json format to print it as string
            Debug.Log(CodePackage(serverPackage));
        }
        catch
        {
            Debug.Log("Utracono informacje!");
        }
    }
    */
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
    public Package GetCurrentMessage()
    {
        return serverPackage;
    }
    
}