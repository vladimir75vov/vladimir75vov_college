using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Windows;

namespace Authorization_Form
{
    static class DBMySQL
    {
        static private string host = "localhost";
        static private int port = 3306;
        static private string dataBase = "mydb";
        static private string userName = "root";
        static private string password = "Vova200375";

        static private DataTable data; // решить!!!

        public static MySqlConnection getDBConnection(string host, string dataBase, int port,
                                                      string userName, string password)
        {
            DBMySQL.host = host;
            DBMySQL.port = port;
            DBMySQL.dataBase = dataBase;
            DBMySQL.userName = userName;
            DBMySQL.password = password;

            return DBMySQL.getDBConnection();
        }

        public static MySqlConnection getDBConnection()
        {
            string connectionString = "Server=" + DBMySQL.host + ";Database=" + DBMySQL.dataBase + ";port=" + DBMySQL.port + ";User Id=" + DBMySQL.userName + ";password=" + DBMySQL.password;

            MySqlConnection connection = new MySqlConnection(connectionString);

            return connection;
        }
        public static MySqlCommand getDBCommand(string sql, MySqlConnection mySqlConnection)
        {
            return new MySqlCommand(sql, mySqlConnection);
        }
        public static MySqlDataReader getDBReader(MySqlCommand mySqlCommand)
        {
            return mySqlCommand.ExecuteReader();
        }

        //////// get

        public static DataTable executingSQLCommand(string sql)
        {
            MySqlConnection connection = DBMySQL.getDBConnection();

            connection.Open();
            MySqlCommand command = DBMySQL.getDBCommand(sql, connection);
            MySqlDataReader reader = DBMySQL.getDBReader(command);

            DataTable dataTable = new DataTable();
            dataTable.Load(reader);

            reader.Close();
            reader.Dispose();
            connection.Close();
            connection.Dispose();

            return dataTable;
        }

        public static string[] getDBArrayDataLine(DataTable dataTable, int line)
        {
            string[] stringLine = new string[dataTable.Columns.Count];

            for (int i = 0; i < stringLine.Length; i++)
            {
                stringLine[i] = dataTable.Rows[line][i].ToString();
            }
            return stringLine;
        }
        public static string[] getDBArrayDataColumn(DataTable dataTable, int column)
        {
            string[] stringColumn = new string[dataTable.Rows.Count];

            for (int i = 0; i < stringColumn.Length; i++)
            {
                stringColumn[i] = dataTable.Rows[i][column].ToString();
            }
            return stringColumn;
        }
        public static string getDBStringDataIndex(DataTable dataTable, int line, int column)
        {
            return dataTable.Rows[line][column].ToString();
        }
    }
}
