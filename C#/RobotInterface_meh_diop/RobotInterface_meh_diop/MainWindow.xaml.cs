using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RobotInterface_meh_diop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            buttonEnvoyer.Background = Brushes.Beige;
            textBoxReception.Text = "Recu : " + textBoxEmission.Text;
            //textBoxReception.Text = textBoxEmission.Text;
            //textBoxEmission.Clear();
            //return; en faite ca change rien 
           
            KeyEventHandler textBoxEmission.KeyUp;

        }
    }
}