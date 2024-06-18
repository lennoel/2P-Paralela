using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication10
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "archivos JPG|*.jpg|archivos bmp|*.bmp|archivos png|*.png";
            openFileDialog1.ShowDialog();
            Bitmap bmp = new Bitmap(openFileDialog1.FileName);
            pictureBox1.Image = bmp;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "archivos JPG|*.jpg|archivos bmp|*.bmp|archivos png|*.png";
            openFileDialog1.ShowDialog();
            Bitmap bmp = new Bitmap(openFileDialog1.FileName);
            pictureBox2.Image = bmp;
        }

        private void button3_Click(object sender, EventArgs e)
        {
             Bitmap bmp1 = (Bitmap)pictureBox1.Image;
            Bitmap bmp2 = (Bitmap)pictureBox2.Image;
            Color c = new Color();
            for (int i = 0; i < bmp2.Width; i++)
            {
                for (int j = 0; j < bmp2.Height; j++)
                {
                    c = bmp2.GetPixel(i, j);
                    if (c.R == 0 && c.G == 0 && c.B == 0)
                    {
                        bmp1.SetPixel(i, j, Color.FromArgb(0, 0, 0));
                    }
                }
            }
            pictureBox3.Image = bmp1;
        
        }
        private void button4_Click(object sender, EventArgs e)
        {
            Bitmap bmp2 = (Bitmap)pictureBox1.Image;
            Bitmap bmp1 = (Bitmap)pictureBox2.Image;

            if (bmp1.Width != bmp2.Width || bmp1.Height != bmp2.Height)
            {
                MessageBox.Show("Las imágenes deben tener el mismo tamaño.");
                return;
            }

            Bitmap resultBmp = new Bitmap(bmp1.Width, bmp1.Height);

            for (int i = 0; i < bmp1.Width; i++)
            {
                for (int j = 0; j < bmp1.Height; j++)
                {
                    Color c1 = bmp1.GetPixel(i, j);
                    Color c2 = bmp2.GetPixel(i, j);

                    // Calcula la resta de los valores RGB
                    int r = Math.Max(0, c1.R - c2.R);
                    int g = Math.Max(0, c1.G - c2.G);
                    int b = Math.Max(0, c1.B - c2.B);

                    // Mantén la transparencia si ambos píxeles son completamente transparentes
                    if (c1.A == 0 && c2.A == 0)
                    {
                        resultBmp.SetPixel(i, j, Color.FromArgb(0, 0, 0, 0));
                    }
                    else
                    {
                        resultBmp.SetPixel(i, j, Color.FromArgb(r, g, b));
                    }
                }
            }

            pictureBox4.Image = resultBmp;
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        
    }
}
