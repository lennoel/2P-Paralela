using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;

namespace ClassLibrary1
{
    public class Class1
    {
        private string connectionString = "server=DESKTOP-A0Q6UBA\\SQLGRINSHOW;user=sa;pwd=123456;database=AlumnoDB";
        public DataSet alummno()
        {
            SqlConnection con = new SqlConnection();
            con.ConnectionString = "server=DESKTOP-A0Q6UBA\\SQLGRINSHOW;user=sa;pwd=123456;database=AlumnoDB";

            SqlDataAdapter ada = new SqlDataAdapter();
            ada.SelectCommand = new SqlCommand();
            ada.SelectCommand.Connection = con;
            ada.SelectCommand.CommandText = "select * from Alumno";
            DataSet ds = new DataSet();
            ada.Fill(ds);
            return ds;
        }
        public DataSet ObtenerAlumnoPorCI(int ci)
        {
            using (SqlConnection con = new SqlConnection(connectionString))
            {
                SqlDataAdapter ada = new SqlDataAdapter();
                ada.SelectCommand = new SqlCommand("select * from Alumno where CI = @CI", con);
                ada.SelectCommand.Parameters.AddWithValue("@CI", ci);

                DataSet ds = new DataSet();
                ada.Fill(ds);
                return ds;
            }
        }

    }
}
