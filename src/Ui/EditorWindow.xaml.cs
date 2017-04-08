using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Xml;

namespace Ui
{
    public partial class EditorWindow : Window
    {
        private const string AboutText = "This is a simple simulation toolkit for RBF's & MLP's for the GameAI module";

        public EditorWindow()
        {
            InitializeComponent();

            MLPErrorThreshold.Text = "0.01";
            MLPLearningRate.Text = "0.1";
            MLPEpochs.Text = "500";

            RBFErrorThreshold.Text = "0.01";
            RBFLearningRate.Text = "0.1";
            RBFEpochs.Text = "500";

            NoiseComboBox.SelectedIndex = 2;
            NoiseComboBox.ItemsSource = new List<string>() { "0.20", "0.10", "0.05" };

            TrainingComboBox.SelectedIndex = 1;
            TrainingComboBox.ItemsSource = new List<string>() { "5", "10", "20" };
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (sender == Exit)
                Application.Current.Shutdown();
            else if (sender == About)
                MessageBox.Show(AboutText, "About", MessageBoxButton.OK, MessageBoxImage.Information);
            else if (sender == Run)
                RunSimulator();
        }

        private bool TestInputValues(params string[] arguments)
        {
            var passes = 0;
            var val = 0.0;

            foreach (string str in arguments)
            {
                if (double.TryParse(str, out val))
                {
                    ++passes;
                }
            }

            return (passes == arguments.Length);
        }

        private void RunSimulator()
        {
            if (TestInputValues(MLPErrorThreshold.Text, MLPLearningRate.Text, MLPEpochs.Text))
            {
                if (TestInputValues(RBFErrorThreshold.Text, RBFLearningRate.Text, RBFEpochs.Text))
                {
                    try
                    {
                        var settings = new XmlDocument();
                        settings.Load(@"settings.xml");
                        settings.SelectSingleNode("/Settings/SettingsMLP/ErrorThreshold").InnerText = MLPErrorThreshold.Text;
                        settings.SelectSingleNode("/Settings/SettingsMLP/LearningRate").InnerText = MLPLearningRate.Text;
                        settings.SelectSingleNode("/Settings/SettingsMLP/Iterations").InnerText = MLPEpochs.Text;
                        settings.SelectSingleNode("/Settings/SettingsRBF/ErrorThreshold").InnerText = RBFErrorThreshold.Text;
                        settings.SelectSingleNode("/Settings/SettingsRBF/LearningRate").InnerText = RBFLearningRate.Text;
                        settings.SelectSingleNode("/Settings/SettingsRBF/Iterations").InnerText = RBFEpochs.Text;
                        settings.SelectSingleNode("/Settings/TrainingData").InnerText = TrainingComboBox.Text;
                        settings.SelectSingleNode("/Settings/Noise").InnerText = NoiseComboBox.Text;
                        settings.Save(@"settings.xml");

                        Process.Start("Network.exe");
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.Message);
                    }
                }
                else
                {
                    MessageBox.Show("RBF Input Boxes do not contain valid values");
                }
            }
            else
            {
                MessageBox.Show("MLP Input Boxes do not contain valid values");
            }
        }
    }
}
