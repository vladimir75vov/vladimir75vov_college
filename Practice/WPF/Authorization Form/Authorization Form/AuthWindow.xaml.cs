using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Authorization_Form
{
    public partial class AuthWindow : Window
    {
        public AuthWindow()
        {
            InitializeComponent();
        }

        private void Button_Auth_Click(object sender, RoutedEventArgs e)
        {
            DataTable auth = DBMySQL.executingSQLCommand($"SELECT login, pass FROM `user` WHERE(login = '{textboxLogin.Text}') AND(pass = '{passwordBoxPass.Password}')");
            if (auth.Rows.Count == 1)
                MessageBox.Show("Усмешная авторизация!");
            else
                MessageBox.Show("Неправельный логин или пароль!");
        }

        private void Button_Reg_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.Show();
            Hide();
        }
    }
}
