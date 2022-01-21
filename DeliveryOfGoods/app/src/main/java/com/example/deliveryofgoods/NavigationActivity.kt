package com.example.deliveryofgoods

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class NavigationActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.navigation_layout)
    }

    fun onClickPickUpActivity(view: View)
    {
        val randomIntent = Intent(this, PickUpActivity::class.java)
        startActivity(randomIntent)
    }
    fun onClickRegisterOfOrderActivity(view: View)
    {
        val randomIntent = Intent(this, RegisterOfOrderActivity::class.java)
        startActivity(randomIntent)
    }
    fun onClickStatisticActivity(view: View)
    {
        val randomIntent = Intent(this, StatisticActivity::class.java)
        startActivity(randomIntent)
    }
    fun onClickAdminActivity(view: View)
    {
        val randomIntent = Intent(this, AdminActivity::class.java)
        startActivity(randomIntent)
    }
}