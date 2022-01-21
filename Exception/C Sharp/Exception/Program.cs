using System;
using System.Text;

namespace Exception
{
    class Program
    {
        static int zero(int a, int b)
        {
            try
            {
                return a / b;
            }
            catch
            {
                Console.WriteLine("Делить на ноль нельзя!");
                return 1;
            }
        }

        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;

            int a = int.Parse(Console.ReadLine());
            int b = int.Parse(Console.ReadLine());

            Console.WriteLine(zero(a, b));

            Console.WriteLine(typeof(int));
            Console.WriteLine(typeof(float));

            // int = 4 байта;
            // float = 4 байта;
        }
    }
}
