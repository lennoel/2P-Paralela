using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ClassLibrary1.Class1 c1 = new ClassLibrary1.Class1();
            this.dataGridView1.DataSource = c1.alummno().Tables[0];
        }

        private void label1_Click(object sender, EventArgs e)
        {
            int ci;
            if (int.TryParse(txtCI.Text, out ci))
            {
                ClassLibrary1.Class1 c1 = new ClassLibrary1.Class1();
                DataSet ds = c1.ObtenerAlumnoPorCI(ci);
                if (ds.Tables[0].Rows.Count > 0)
                {
                    dataGridView1.DataSource = ds.Tables[0];
                }
                else
                {
                    MessageBox.Show("No se encontró al alumno con el CI especificado.");
                }
            }
            else
            {
                MessageBox.Show("Por favor, ingrese un CI válido.");
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnBuscar_Click(object sender, EventArgs e)
        {

            int ci;
            if (int.TryParse(txtCI.Text, out ci))
            {
                ClassLibrary1.Class1 c1 = new ClassLibrary1.Class1();
                DataSet ds = c1.ObtenerAlumnoPorCI(ci);
                if (ds.Tables[0].Rows.Count > 0)
                {
                    dataGridView1.DataSource = ds.Tables[0];
                }
                else
                {
                    MessageBox.Show("No se encontró al alumno con el CI especificado.");
                }
            }
            else
            {
                MessageBox.Show("Por favor, ingrese un CI válido.");
            }
        }
    }
}
