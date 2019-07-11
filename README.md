# Steering-UNITY-game-by-wireless-controller
First big project

Hello!

Concept of this project is to create  connection between Unity instantion and Myo armband, and use it to control
Unity game object. 
Final conception is to create a library, that will ensure easy connection, retrieving and operating with real-time raw Myo data in 
user friendly form.

Before using the Myo armband, i created an enviroment that will make my work easier.
On the server side (UNITY), i created a connection with QTapplication using TCP/IP SOCKET. I will connect QT app with Myo band via bluetooth,
and then send the data retrieved from band to Unity via already established connection.

