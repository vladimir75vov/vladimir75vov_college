package com.example.deliveryofgoods

import android.content.Intent
import android.content.SharedPreferences
import android.os.Bundle
import android.text.TextUtils
import android.view.View
import android.widget.Button
import android.widget.CheckBox
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.auth.ktx.auth
import com.google.firebase.ktx.Firebase

class AuthenticationActivity: AppCompatActivity() {
    private lateinit var authFirebaseAuth: FirebaseAuth;
    private lateinit var loginEditText: EditText
    private lateinit var passEditText: EditText
    private lateinit var button: Button
    private lateinit var automaticLoginCheckBox: CheckBox
    private lateinit var pref: SharedPreferences


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.authentication_layout)
        init()
    }
    private fun init()
    {
        authFirebaseAuth = Firebase.auth
        loginEditText = findViewById(R.id.editTextLogin)
        passEditText = findViewById(R.id.editTextPass)
        button = findViewById(R.id.buttonSignIn)
        automaticLoginCheckBox = findViewById(R.id.checkBoxSaveAuthentication)
        pref = getSharedPreferences("authentication", MODE_PRIVATE)
        if(pref.getBoolean("automaticLogin",false))
        {
            onClickLoadAuthentication()
        }

    }
    public override fun onStart()
    {
        super.onStart()
        //val currentUser = auth.currentUser
    }
    fun isEmailValid(email: String): Boolean {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()
    }

    private fun onClickSignIn()
    {
        if(!TextUtils.isEmpty(loginEditText.text.toString()) and !TextUtils.isEmpty(passEditText.text.toString()))
        {
            if(!isEmailValid(loginEditText.text.toString()))
            {
                loginEditText.setText(loginEditText.text.toString()+"@leroymerlin.ru")
            }
            authFirebaseAuth.signInWithEmailAndPassword(loginEditText.text.toString(),passEditText.text.toString()).addOnCompleteListener(this)
            {
                task ->
                if (task.isSuccessful)
                {
                    Toast.makeText(this,"Пользователь успешно зашел",Toast.LENGTH_SHORT).show()
                    onClickSaveAuthentication()
                    val randomIntent = Intent(this, NavigationActivity::class.java)
                    startActivity(randomIntent)
                }
                else
                {
                    Toast.makeText(this,"Ошибка входа",Toast.LENGTH_SHORT).show()
                }
            }
        }
    }
    fun onClickSignIn(view: View)
    {
        onClickSignIn()
    }
    private fun onClickLoadAuthentication()
    {
        loginEditText.setText(pref.getString("login",""))
        passEditText.setText(pref.getString("pass",""))
        automaticLoginCheckBox.isChecked = pref.getBoolean("automaticLogin",false)
        onClickSignIn()
    }

    private fun onClickSaveAuthentication()
    {
        val editor = pref.edit()
        editor.putBoolean("automaticLogin",automaticLoginCheckBox.isChecked)
        editor.putString("login",loginEditText.text.toString())
        editor.putString("pass",passEditText.text.toString())
        editor.apply()
    }

}