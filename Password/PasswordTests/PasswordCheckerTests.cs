using Microsoft.VisualStudio.TestTools.UnitTesting;
using ClassLibraryPassword;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibraryPassword.Tests
{
    [TestClass()]
    public class PasswordCheckerTests
    {
        [TestMethod()]
        public void Check_8Symbols_ReturnsTrue()
        {
            // Arrange
            string password = "Glist_zabivnoi2004";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_4Symbols_ReturnsFalse()
        {
            // Arrange
            string password = "Put";
            bool expected = false;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_8Numbers_ReturnsTrue()
        {
            // Arrange
            string password = "12345678aBc()";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_4Numbers_ReturnsFalse()
        {
            // Arrange
            string password = "Odin";
            bool expected = false;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_8SpecialSymbols_ReturnsTrue()
        {
            // Arrange
            string password = "Donba_12345S";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_4SpecialSymbols_ReturnsFalse()
        {
            // Arrange
            string password = "qwert$$$$";
            bool expected = false;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_8Uppercase_ReturnsTrue()
        {
            // Arrange
            string password = "Sueta2007_";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_4Uppercase_ReturnsFalse()
        {
            // Arrange
            string password = "asswecan";
            bool expected = false;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_8Lowercase_ReturnsTrue()
        {
            // Arrange
            string password = "qazWER!@43";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_4Lowercase_ReturnsFalse()
        {
            // Arrange
            string password = "DUNGEON_MASTER";
            bool expected = false;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_4Latiniha_ReturnsTrue()
        {
            // Arrange
            string password = "ФaP20_ggggga";
            bool expected = false;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
    }
}