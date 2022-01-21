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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Сalculator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            foreach(UIElement el in mainForm.Children)
            {
                if(el is Button)
                {
                    ((Button)el).Click += Button_Click;
                }
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string contentButtton = (string)((Button)e.OriginalSource).Content;

            if (contentButtton == "C")
                textBlockOutput.Text = null;
            else if (contentButtton == "X")
                textBlockOutput.Text += "*";
            else if (contentButtton == "÷")
                textBlockOutput.Text += "/";
            else if (contentButtton == "⇦")
                textBlockOutput.Text = textBlockOutput.Text.Remove(textBlockOutput.Text.Length - 1);
            else if (contentButtton == "±")
            {
                if (textBlockOutput.Text[0] == '-')
                    textBlockOutput.Text = textBlockOutput.Text.Substring(1);
                else
                    textBlockOutput.Text = "-" + textBlockOutput.Text;
            }
            else if (contentButtton == "=")
            {
                try
                {
                    string value = Convert.ToString(new DataTable().Compute(textBlockOutput.Text, ""));
                    textBlockOutput.Text = value;
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Ошибка: {ex}");
                }
            }
            else
                textBlockOutput.Text += contentButtton;
        }
    }
}
