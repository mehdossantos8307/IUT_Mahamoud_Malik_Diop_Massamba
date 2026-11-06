//using System.IO.Ports;
//using System.Net;
//using System.Text;
//using System.Windows;
//using System.Windows.Controls;
//using System.Windows.Data;
//using System.Windows.Documents;
//using System.Windows.Input;
//using System.Windows.Media;
//using System.Windows.Media.Imaging;
//using System.Windows.Navigation;
//using System.Windows.Shapes;
//using ExtendedSerialPort_NS ;

//namespace RobotInterface_meh_diop
//{
//    /// <summary>
//    /// Interaction logic for MainWindow.xaml
//    /// </summary>
//    public partial class MainWindow : Window
//    {
//        ExtendedSerialPort serialPort1;
//        public MainWindow()
//        {
//            InitializeComponent();
//            serialPort1 = new ExtendedSerialPort("COM4", 115200, Parity.None, 8, StopBits.One);
//            serialPort1.DataReceived += SerialPort1_DataReceived;
//            serialPort1.Open();

//        }
//        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
//        { }
//        bool boutonEstBleu = false;
//        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
//        {
//            // Alternance de couleur : si c'est bleu on passe en beige, sinon en bleu
//            if (boutonEstBleu == true)
//            {
//                buttonEnvoyer.Background = Brushes.Beige;
//                boutonEstBleu = false;
//            }
//            else
//            {
//                buttonEnvoyer.Background = Brushes.RoyalBlue;
//                boutonEstBleu = true;
//            }

//            SendMessage();  

//        }

//private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
//        {
//            if (e.Key == Key.Enter)   // si la touche relâchée est Entrée
//            {
//                SendMessage();
//            }
//        }


//        void SendMessage()
//        {
//            // On récupère le texte et Trim() enlève le retour à la ligne laissé par Entrée
//            string message = textBoxEmission.Text.Trim();

//            // On n'envoie que s'il reste vraiment quelque chose à envoyer
//            if (message != "")
//            {
//                serialPort1.WriteLine(message);   // envoi sur le port série
//            }

//            // On vide la case dans tous les cas (même s'il n'y avait qu'un retour à la ligne)
//            textBoxEmission.Text = "";
//        }

//    }
//}



using System.IO.Ports;
using System.Net;            
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
using ExtendedSerialPort_NS; // la bibliothèque du prof (ExtendedSerialPort, DataReceivedArgs)

namespace RobotInterface_meh_diop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    // "partial" : la classe est répartie sur 2 fichiers -> le XAML (le dessin) et ce .cs (le comportement).
    // ": Window" : MainWindow hérite de tout ce que sait faire une fenêtre.
    public partial class MainWindow : Window
    {
        // Déclarée dans la classe (hors des fonctions) pour être utilisable par TOUTES les fonctions.
        // Vide ici : le port est vraiment créé plus bas avec "new".
        ExtendedSerialPort serialPort1;

        // Constructeur : appelé UNE seule fois au lancement (comme les Init...() du main sur le dsPIC).
        public MainWindow()
        {
            InitializeComponent(); // construit les éléments décrits dans le XAML, toujours en premier

            // Les réglages doivent être identiques des deux côtés de la liaison (115200 bauds, 8 bits, pas de parité, 1 stop)
            serialPort1 = new ExtendedSerialPort("COM4", 115200, Parity.None, 8, StopBits.One);

            // += : "quand des données arrivent, appelle SerialPort1_DataReceived" (abonnement à l'événement)
            serialPort1.DataReceived += SerialPort1_DataReceived;

            serialPort1.Open(); // plante ici si COM4 n'existe pas ou est déjà utilisé par un autre programme
        }

        // Appelée AUTOMATIQUEMENT par le port série à chaque réception.
        // e.Data = le tableau d'octets reçus.
        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        { }

        // Déclarée hors de la fonction pour GARDER sa valeur entre deux clics
        // (à l'intérieur, elle serait recréée à false à chaque clic).
        bool boutonEstBleu = false;

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            // Alternance de couleur : si c'est bleu on passe en beige, sinon en bleu
            if (boutonEstBleu == true)
            {
                buttonEnvoyer.Background = Brushes.Beige;
                boutonEstBleu = false;
            }
            else
            {
                buttonEnvoyer.Background = Brushes.RoyalBlue;
                boutonEstBleu = true;
            }

            SendMessage();
        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)   // si la touche relâchée est Entrée
            {
                SendMessage();
            }
        }

        // Une seule fonction d'envoi pour le bouton ET la touche Entrée :
        // si on doit la modifier, on ne le fait qu'à un endroit.
        void SendMessage()
        {
            // Trim() enlève le retour à la ligne ajouté par la touche Entrée
            string message = textBoxEmission.Text.Trim();

            if (message != "")
            {
                serialPort1.WriteLine(message); // WriteLine ajoute lui-même un retour à la ligne à la fin
            }

            textBoxEmission.Text = ""; // on vide la case dans tous les cas
        }
    }
}