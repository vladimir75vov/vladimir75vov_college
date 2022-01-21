using MySql.Data.MySqlClient;
using System;
using System.Data;
using System.Linq;
using System.Windows;
using System.Windows.Media;

namespace Authorization_Form
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        public bool validateLogin(string login)
        {
            if (login.Length < 3 || login.Length > 20)
                return false;

            return true;
        }

        public bool validatePassword(string password)
        {
            if (password.Length < 8 || password.Length > 20)
                return false;

            if (!password.Any(Char.IsLower))
                return false;

            if (!password.Any(Char.IsUpper))
                return false;

            if (!password.Any(Char.IsDigit))
                return false;

            if (password.Intersect("!@#$%^&*()_+=-<>,./?';:\\|").Count() == 0)
                return false;

            return true;
        }

        public bool validatePasswordSecond(string passwordOne, string passwordTwo)
        {
            if (passwordOne != passwordTwo)
                return false;

            return true;
        }

        public bool validateEmail(string email)
        {
            if (email.Length < 3)
                return false;

            if (!email.Contains("@") || !email.Contains("."))
                return false;

            return true;
        }

        public bool validate(string login, string passOne, string passTwo, string email)
        {
            string toolTip = "Это поле введено не корректно!";

            SolidColorBrush brushesError = Brushes.PaleVioletRed;
            SolidColorBrush brushesAccses = Brushes.Transparent;

            if (validateLogin(login) == false)
            {
                textBoxLogin.ToolTip = toolTip;
                textBoxLogin.Background = brushesError;

                return false;
            }
            else
            {
                DataTable auth = DBMySQL.executingSQLCommand($"SELECT login FROM `user` WHERE(login = '{login}')");
                if (auth.Rows.Count == 1)
                {
                    textBoxLogin.ToolTip = toolTip + "\nЛогин уже занят";
                    textBoxLogin.Background = brushesError;
                    return false;
                }
                    
            }

            textBoxLogin.ToolTip = "";
            textBoxLogin.Background = brushesAccses;

            if (validatePassword(passOne) == false)
            {
                passwordBoxPassOne.ToolTip = toolTip + "\nПароль должен быть не менее 8 символов и не более 20 символов, содержать комбинацию цифр, строчных и заглавных букв, а также спец. символ";
                passwordBoxPassOne.Background = brushesError;

                return false;
            }

            passwordBoxPassOne.ToolTip = "";
            passwordBoxPassOne.Background = brushesAccses;

            if (validatePasswordSecond(passOne, passTwo) == false)
            {
                passwordBoxPassTwo.ToolTip = toolTip + "\nПароли должны совпадать";
                passwordBoxPassTwo.Background = brushesError;

                return false;
            }

            passwordBoxPassTwo.ToolTip = "";
            passwordBoxPassTwo.Background = brushesAccses;


            if (validateEmail(email) == false)
            {
                textBoxEmail.ToolTip = toolTip + "\nТакой почти не существует";
                textBoxEmail.Background = brushesError;

                return false;
            }
            else
            {
                DataTable auth = DBMySQL.executingSQLCommand($"SELECT login FROM `email` WHERE(email = '{email}')");
                if (auth.Rows.Count == 1)
                {
                    textBoxEmail.ToolTip = toolTip + "\nEmail уже используется";
                    textBoxEmail.Background = brushesError;
                    return false;
                }

            }

            textBoxEmail.ToolTip = "";
            textBoxEmail.Background = brushesAccses;

            return true;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string login = textBoxLogin.Text.Trim();
            string passOne = passwordBoxPassOne.Password.Trim();
            string passTwo = passwordBoxPassTwo.Password.Trim();
            string email = textBoxEmail.Text.Trim().ToLower();

            if (validate(login, passOne, passTwo, email) == true)
            {
                try
                {
                    DBMySQL.executingSQLCommand($"INSERT INTO `mydb`.`user` (`login`, `pass`, `email`) VALUES ('{login}', '{passOne}', '{email}');");
                }
                catch (Exception er)
                {
                    MessageBox.Show($"Произошла ошибка с соединением с сервером! \n\n{er}");
                }

            }
        }

        private void Button_Click_Enter(object sender, RoutedEventArgs e)
        {
            AuthWindow AuthWindow = new AuthWindow();
            AuthWindow.Show();
            Hide();
        }
    }
}
