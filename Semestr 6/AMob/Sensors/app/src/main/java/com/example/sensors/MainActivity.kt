package com.example.sensors

import android.annotation.SuppressLint
import android.app.NotificationChannel
import android.app.NotificationManager
import android.content.Context
import android.content.pm.PackageManager
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.location.Location
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import com.google.android.gms.location.FusedLocationProviderClient
import com.google.android.gms.location.LocationServices

class MainActivity : AppCompatActivity(), SensorEventListener {

    private lateinit var fusedLocationProviderClient : FusedLocationProviderClient

    private lateinit var sensorManager : SensorManager
    private var lightSensor : Sensor ?= null
    private var temperatureSensor : Sensor ?= null
    private var accelerationSensor : Sensor ?= null
    private var humiditySensor : Sensor ?= null

    private lateinit var coordinatesTextView : TextView
    private lateinit var lightTextView : TextView
    private lateinit var temperatureTextView : TextView
    private lateinit var accelerationTextView : TextView
    private lateinit var humidityTextView : TextView
    private lateinit var sendNotificationButton: Button

    private val CHANNEL_ID = "temp_notification_channel"
    private val notificationId = 101

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        fusedLocationProviderClient = LocationServices.getFusedLocationProviderClient(this)

        this.getLocation()

        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager

        lightSensor = sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT)
        temperatureSensor = sensorManager.getDefaultSensor(Sensor.TYPE_AMBIENT_TEMPERATURE)
        accelerationSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
        humiditySensor = sensorManager.getDefaultSensor(Sensor.TYPE_RELATIVE_HUMIDITY)

        coordinatesTextView = findViewById(R.id.coordinatesTextView)
        lightTextView = findViewById(R.id.lightTextView)
        temperatureTextView = findViewById(R.id.temperatureTextView)
        accelerationTextView = findViewById(R.id.accelerationTextView)
        humidityTextView = findViewById(R.id.humidityTextView)

//        createNotificationChannel()

    }

    @SuppressLint("SetTextI18n")
    override fun onSensorChanged(event: SensorEvent?) {
        if(event != null) {
            val sensorType = event.sensor.type


            if(sensorType == Sensor.TYPE_LIGHT) {
                lightTextView.text = "Light: " + event.values[0].toString() + "\n"
            }
            if(sensorType == Sensor.TYPE_AMBIENT_TEMPERATURE) {
                temperatureTextView.text = "Temperature: " + event.values[0].toString() + "\n"
            }
            if(sensorType == Sensor.TYPE_ACCELEROMETER) {
                accelerationTextView.text = "Accelerometer: " + "\nX: " + event.values[0].toString() +
                                                                "\nY: " + event.values[1].toString() +
                                                                "\nZ: " + event.values[2].toString() + "\n"
            }
            if(sensorType == Sensor.TYPE_RELATIVE_HUMIDITY) {
                humidityTextView.text = "Humidity: " + event.values[0].toString()
            }
        }
    }

    override fun onAccuracyChanged(p0: Sensor?, p1: Int) {
        print("Accuracy changed")
    }

    override fun onResume() {
        super.onResume()
        sensorManager.registerListener(this, lightSensor, SensorManager.SENSOR_DELAY_NORMAL)
        sensorManager.registerListener(this, temperatureSensor, SensorManager.SENSOR_DELAY_NORMAL)
        sensorManager.registerListener(this, accelerationSensor, SensorManager.SENSOR_DELAY_NORMAL)
        sensorManager.registerListener(this, humiditySensor, SensorManager.SENSOR_DELAY_NORMAL)
    }

    override fun onPause() {
        super.onPause()
        sensorManager.unregisterListener(this, lightSensor)
        sensorManager.unregisterListener(this, accelerationSensor)
        sensorManager.unregisterListener(this, humiditySensor)

        while(true) {
            sendNotification()
            Thread.sleep(12000)
        }
    }

    @SuppressLint("SetTextI18n")
    private fun getLocation() {
        if (ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED &&
            ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {

            ActivityCompat.requestPermissions(this, arrayOf(android.Manifest.permission.ACCESS_FINE_LOCATION), 44)
            ActivityCompat.requestPermissions(this, arrayOf(android.Manifest.permission.ACCESS_COARSE_LOCATION), 44)
            return
        }

        fusedLocationProviderClient.lastLocation.addOnSuccessListener(this) { location: Location? ->
            coordinatesTextView.text = "Position: " + location!!.latitude.toString() + ", " + location.longitude.toString() + "\n"
        }
    }

    private fun sendNotification() {
        val builder = NotificationCompat.Builder(this, CHANNEL_ID)
            .setSmallIcon(R.drawable.ic_launcher_background)
            .setContentTitle("Temperature notification")
            .setContentText("elemeledudki: ${temperatureTextView.text.toString()}")
            .setPriority(NotificationCompat.PRIORITY_DEFAULT)

        with(NotificationManagerCompat.from(this)) {
            notify(notificationId, builder.build())
        }
    }

//    private fun createNotificationChannel() {
//        val name = "Temperature notification"
//        val descriptionText = temperatureTextView.text.toString()
//        val importance = NotificationManager.IMPORTANCE_DEFAULT
//        val channel = NotificationChannel(CHANNEL_ID, name, importance).apply {
//            description = descriptionText
//        }
//        val notificationManager: NotificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
//        notificationManager.createNotificationChannel(channel)
//    }
}
