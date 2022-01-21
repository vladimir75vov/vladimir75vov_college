using System;
using System.Text;

namespace Calculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;

            Console.WriteLine("Первое число: ");
            string doubleOne = Console.ReadLine();

            Console.WriteLine("Действие %, *, /, +, - : ");
            string action = Console.ReadLine();

            Console.WriteLine("Второе число: ");
            string doubleTwo = Console.ReadLine();

            Calculator calculator = new Calculator();

            Console.WriteLine($"Результат: {calculator.Calculate(doubleOne, action, doubleTwo)}");
        }
    }
}

