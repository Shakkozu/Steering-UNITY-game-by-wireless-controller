using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Net;
using System.Net.Sockets;
using System.Net.NetworkInformation;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using UnityEngine.UI;

public class TCPSocket : MonoBehaviour
{

    TcpClient clientSocket;
    public string serverIP;


    private Thread tListenner;

    public bool running;

    public bool SearchServer()
    {
        Debug.Log("Connecting");

        try
        {
            clientSocket = new TcpClient("127.0.0.1", 10000);
            byte[] pack = new byte[256];
            var response = "PING" + ',' + "^^!!!";
            pack = Encoding.ASCII.GetBytes(response);
            NetworkStream networkStream = clientSocket.GetStream();
            networkStream.Write(pack, 0, pack.Length);
            networkStream.Close();


            Debug.Log("Server" + serverIP);
            Debug.Log("Connected");
            return true;
        }
        catch
        {
            return false;

        }
        // return false;

    }


    // connect
    public void StartTCPServer()
    {


        if (tListenner != null && tListenner.IsAlive)
        {
            //    disconnect();
            while (tListenner != null && tListenner.IsAlive)
            {


            }
        }

        // start  listener thread
        tListenner = new Thread(
            new ThreadStart(OnListeningClients));
        tListenner.IsBackground = true;
        tListenner.Start();

    }



    public void OnListeningClients()
    {

        try
        {
            Debug.Log("starting server");
            IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());


            TcpListener tcpListener = new TcpListener(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5000));
            tcpListener.Start();

            while (running)
            {
                if (tcpListener.Pending())
                {
                    TcpClient tcpClient = tcpListener.AcceptTcpClient();

                    byte[] pack = new byte[256];
                    NetworkStream ns = tcpClient.GetStream();
                    ns.Read(pack, 0, pack.Length);

                    // CanvasManager.instance.ShowAlertDialog(Encoding.ASCII.GetString(pack));
                }

                else
                {
                    Thread.Sleep(500);
                }
            }
        }
        catch
        {
            throw;
        }
    }



}
//using UnityEngine;
//using System.Collections;
//using System;
//using System.IO;
//using System.Net.Sockets;
//public class s_TCP : MonoBehaviour
//{
//    internal Boolean socketReady = false;
//    TcpClient mySocket;
//    NetworkStream theStream;
//    StreamWriter theWriter;
//    StreamReader theReader;
//    String Host = "localhost";
//    Int32 Port = 10000;
//    void Start()
//    {
//        setupSocket();
//        writeSocket("Hej!");
//        readSocket();
//        closeSocket();
//    }
//    void Update()
//    {
//    }
//     **********************************************
//    public void setupSocket()
//    {
//        try
//        {
//            mySocket = new TcpClient(Host, Port);
//            theStream = mySocket.GetStream();
//            theWriter = new StreamWriter(theStream);
//            theReader = new StreamReader(theStream);
//            socketReady = true;
//        }
//        catch (Exception e)
//        {
//            Debug.Log("Socket error: " + e);
//        }
//    }
//    public void writeSocket(string theLine)
//    {
//        if (!socketReady)
//            return;
//        String foo = theLine + "\r\n";
//        theWriter.Write(foo);
//        theWriter.Flush();
//    }
//    public String readSocket()
//    {
//        if (!socketReady)
//            return "";
//        if (theStream.DataAvailable)
//            return theReader.ReadLine();
//        return "";
//    }
//    public void closeSocket()
//    {
//        if (!socketReady)
//            return;
//        theWriter.Close();
//        theReader.Close();
//        mySocket.Close();
//        socketReady = false;
//    }
//} // end class s_TCP