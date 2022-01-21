using System;
using System.Text;

namespace ClassLibraryPassword
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;

            PasswordChecker passwordChecker = new PasswordChecker();

            Console.Write("Пароль: ");
            Console.WriteLine(passwordChecker.ValidatePassword(Console.ReadLine()));
        }
    }
}
