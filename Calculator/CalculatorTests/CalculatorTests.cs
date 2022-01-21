using Microsoft.VisualStudio.TestTools.UnitTesting;
using Calculator;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Tests
{
    [TestClass()]
    public class CalculatorTests
    {
        /*bool StringIsDigits(string s)
        {
            double num;
            if (double.TryParse(s, out num))
            {
                return true;
            }
            return false;
        }*/

        [TestMethod()]
        public void CheckOperationAddition()
        {
            string doubleOne = "12,1";
            string action = "+";
            string doubleTwo = "12,3";

            double expected = 24.4;

            double actual = Calculator.calculate(doubleOne, action, doubleTwo);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        //[TestMethod()]
/*        public void CheckOperationSubtraction()
        {
            string doubleOne = "12.1";
            string action = "-";
            string doubleTwo = "12.3";

            bool expected = true;

            bool actual = StringIsDigits(Calculator.calculate(doubleOne, action, doubleTwo).ToString());
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void CheckOperationMultiplication()
        {
            string doubleOne = "12.1";
            string action = "*";
            string doubleTwo = "12.3";

            bool expected = true;

            bool actual = StringIsDigits(Calculator.calculate(doubleOne, action, doubleTwo).ToString());
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void CheckOperationDivision()
        {
            string doubleOne = "12.1";
            string action = "/";
            string doubleTwo = "12.3";

            bool expected = true;

            bool actual = StringIsDigits(Calculator.calculate(doubleOne, action, doubleTwo).ToString());
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void CheckOperationPercent()
        {
            string doubleOne = "12.1";
            string action = "%";
            string doubleTwo = "12.3";

            bool expected = true;

            bool actual = StringIsDigits(Calculator.calculate(doubleOne, action, doubleTwo).ToString());
            // Assert
            Assert.AreEqual(expected, actual);
        }*/
        [TestMethod()]
        public void TestDiv_null()
        {
            try
            {
                string a = "25";
                string b = "1";

                string operation = "$";
                double res = 0;
                double actual = Calculator.calculate(a, operation, b);

                Assert.AreEqual(actual, res);
            }
            catch (Exception e)
            {
                Assert.Fail(e.Message);
            }
        }
    }
}