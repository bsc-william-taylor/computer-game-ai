using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Xml;

namespace Trainer
{
    public partial class EditorWindow : Window
    {
        public EditorWindow()
        {
            InitializeComponent();
            SetupDefaultValues();
            SetupComboBox();
        }

        private void SetupDefaultValues()
        {
            MLP_ErrorThreshold.Text = "0.01";
            MLP_LearningRate.Text = "0.1";
            MLP_Epochs.Text = "500";

            RBF_ErrorThreshold.Text = "0.01";
            RBF_LearningRate.Text = "0.1";
            RBF_Epochs.Text = "500";
        }

        private void SetupComboBox()
        {
            List<string> noiseValues = new List<string>();
            noiseValues.Add("0.20");
            noiseValues.Add("0.10");
            noiseValues.Add("0.05");

            NoiseComboBox.ItemsSource = noiseValues;
            NoiseComboBox.SelectedIndex = 2;

            List<string> trainingSetSize = new List<string>();
            trainingSetSize.Add("5");
            trainingSetSize.Add("10");
            trainingSetSize.Add("20");

            TrainingComboBox.ItemsSource = trainingSetSize;
            TrainingComboBox.SelectedIndex = 1;
        }


        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            if(sender == Exit)
            {
                Application.Current.Shutdown();
            }

            if(sender == About)
            {
                MessageBox.Show("This is a simple simulation toolkit for RBF's & MLP's for the GameAI module", "About ", MessageBoxButton.OK);
            }
            
            if(sender == Run)
            {
                RunSimulator();
            }
        }

        private bool TestInputValues(params string[] arguments)
        {
            double dummy;
            int passes = 0;

            foreach(string str in arguments)
            {
                if (double.TryParse(str, out dummy))
                {
                    ++passes;
                }
            }

            return (passes == arguments.Length);
        }

        private void RunSimulator()
        {
            // Test to make sure all values in the input boxes are correct
            if (TestInputValues(MLP_ErrorThreshold.Text, MLP_LearningRate.Text, MLP_Epochs.Text))
            {
                // Test again to make sure all values in the input boxes are correct
                if (TestInputValues(RBF_ErrorThreshold.Text, RBF_LearningRate.Text, RBF_Epochs.Text))
                {
                    try
                    {
                        // Then alter the XML file which will be read by the simulator
                        XmlDocument settings = new XmlDocument();
                        settings.Load(@"settings.xml");

                        // Update the training set values and the noise values in the xml file
                        settings.SelectSingleNode("/Settings/TrainingSet").InnerText = TrainingComboBox.Text;
                        settings.SelectSingleNode("/Settings/Noise").InnerText = NoiseComboBox.Text;

                        // Then update the setting values contained in SettingsMLP xml node
                        settings.SelectSingleNode("/Settings/SettingsMLP/ErrorThreshold").InnerText = MLP_ErrorThreshold.Text;
                        settings.SelectSingleNode("/Settings/SettingsMLP/LearningRate").InnerText = MLP_LearningRate.Text;
                        settings.SelectSingleNode("/Settings/SettingsMLP/Iterations").InnerText = MLP_Epochs.Text;

                        // And last update the setting values contained in SettingsRBF xml node
                        settings.SelectSingleNode("/Settings/SettingsRBF/ErrorThreshold").InnerText = RBF_ErrorThreshold.Text;
                        settings.SelectSingleNode("/Settings/SettingsRBF/LearningRate").InnerText = RBF_LearningRate.Text;
                        settings.SelectSingleNode("/Settings/SettingsRBF/Iterations").InnerText = RBF_Epochs.Text;

                        // The save the updated file & start the simulator
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
                    // on fail say that the paramets in the RBF boxes are incorrect
                    MessageBox.Show("RBF Input Boxes do not contain valid values");
                }
            }
            else
            {
                // on fail say that the paramets in the MLP boxes are incorrect
                MessageBox.Show("MLP Input Boxes do not contain valid values");
            }
        }     
    }
}
