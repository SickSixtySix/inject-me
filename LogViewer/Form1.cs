using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LogViewer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        static void Encrypt(byte[] bytes)
        {
            for (int i = 0; i < bytes.Length; i++)
                bytes[i] = (byte)
                (
                    (bytes[i] & 0x80) >> 1 | (bytes[i] & 0x40) << 1 |   // 7, 6 => 6, 7
                    (bytes[i] & 0x20) >> 1 | (bytes[i] & 0x10) << 1 |   // 5, 4 => 4, 5
                    (bytes[i] & 0x08) >> 1 | (bytes[i] & 0x04) << 1 |   // 3, 2 => 2, 3
                    (bytes[i] & 0x02) >> 1 | (bytes[i] & 0x01) << 1     // 1, 0 => 0, 1
                );
        }

        private void загрузитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() != DialogResult.OK)
                return;

            var bytes = File.ReadAllBytes(openFileDialog1.FileName);
            Encrypt(bytes);
            textBox1.Text = Encoding.Default.GetString(bytes);
        }

        private void сохранитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() != DialogResult.OK)
                return;

            var bytes = Encoding.Default.GetBytes(textBox1.Text);
            Encrypt(bytes);
            File.WriteAllBytes(saveFileDialog1.FileName, bytes);
        }
    }
}
