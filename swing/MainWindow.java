import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * Swing main windows app
 */
public class MainWindow extends JFrame {

    private static final long serialVersionUID = 1L;
    private JLabel outputLine;
    private JavaClient java_client;

    // Constructor
    public MainWindow() {
        // Set window title
        this.setTitle("Remote");

        // Set window default close operation
        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Add menu
        JMenu menu_fichier = new JMenu("Fichier");
        menu_fichier.setMnemonic(KeyEvent.VK_F);
        
        JMenuItem menu_fichier_quitter = new JMenuItem("Quitter");
        menu_fichier_quitter.setMnemonic(KeyEvent.VK_Q);
        menu_fichier_quitter.addActionListener(new QuitListener());
        
        menu_fichier.add(menu_fichier_quitter);

        JMenuBar barre_menu = new JMenuBar();
        barre_menu.add(menu_fichier);
        setJMenuBar(barre_menu);

        JTextPane welcome = new JTextPane();
        welcome.setText("Welcome in the remote. " +
                "\nMultimedia objects available are : \n- photo.png \n- video.mp4" +
                "\nGroups available are : \n- group0");
        welcome.setEditable(false);

        JPanel output_panel = new JPanel();
        output_panel.setLayout(new GridLayout(1, 2));
        outputLine = new JLabel("Disconnected");
        output_panel.add(outputLine);

        add(welcome);
        add(connection_section());
        add(multimedia_section("Multemedia object", "search", "play"));
        add(group_section("Groups", "search_group"));
        add(output_panel);

        pack();

        // Set window visibility
        this.setVisible(true);

    }

    // Connection section, containing inputs for IP address, port and a connection
    // button
    private JPanel connection_section() {
        JPanel connection = new JPanel();
        connection.add(new JLabel("Address:"));
        
        JTextField ip_field = new JTextField("localhost", 20);
        connection.add(ip_field);
        connection.add(new JLabel("Port :"));
        
        JTextField port_field = new JTextField("3331", 10);
        connection.add(port_field);
        
        JButton connect_button = new JButton("Connect");
        connection.add(connect_button);
        connect_button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    if (java_client != null) {
                        java_client.send("stop");
                        java_client.close();
                        java_client = null;
                        connect_button.setText("Connect");
                        outputLine.setText("Disconnected");
                    } else {
                        java_client = new JavaClient(ip_field.getText(), Integer.parseInt(port_field.getText()));
                        outputLine.setText("Connected");
                        connect_button.setText("STOP");
                    }
                } catch (Exception ex) {
                    outputLine.setText("Connecting error");
                }
            }
        });
        
        return connection;
    }

    // Multimedia section, containing a search input, a search button, a play button
    // and a result textArea
    private JComponent multimedia_section(String title, String search_command, String play_command) {
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        
        JPanel tools_panel = new JPanel();
        
        JTextField search_field = new JTextField(20);
        tools_panel.add(search_field);
        
        JButton search_button = new JButton("Rechercher");
        tools_panel.add(search_button);
        
        JButton play_button = new JButton("Jouer");
        tools_panel.add(play_button);
        
        panel.add(tools_panel, BorderLayout.CENTER);
        
        JTextArea text_area = new JTextArea(10, 40);
        text_area.setEditable(false);
        
        search_button.addActionListener(new TcpCommand(search_command, search_field, text_area));
        play_button.addActionListener(new TcpCommand(play_command, search_field, text_area));
        panel.add(new JScrollPane(text_area), BorderLayout.SOUTH);
        return panel;
    }

    // Multimedia section, containing a search input, a search button
    // and a result textArea
    private JComponent group_section(String title, String search_command) {
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        
        JPanel tools_panel = new JPanel();
        
        JTextField search_field = new JTextField(20);
        tools_panel.add(search_field);
        
        JButton search_button = new JButton("Rechercher");
        tools_panel.add(search_button);
        
        panel.add(tools_panel, BorderLayout.CENTER);

        JTextArea text_area = new JTextArea(10, 40);
        text_area.setEditable(false);
        
        search_button.addActionListener(new TcpCommand(search_command, search_field, text_area));
        panel.add(new JScrollPane(text_area), BorderLayout.SOUTH);
        return panel;
    }

    // Update the output line with the given text
    private void set_output_line(String text) {
        outputLine.setText(text);
    }

    // Listener for all the play and search buttons, sending commands to the server
    private class TcpCommand implements ActionListener {
        private String command;
        private JTextField input;
        private JTextArea output;

        public TcpCommand(String command, JTextField input, JTextArea output) {
            this.command = command;
            this.input = input;
            this.output = output;
        }

        public void actionPerformed(ActionEvent e) {
            try {
                if (java_client == null) {
                    set_output_line("Disconnected");
                    this.output.setText("Disconnected");
                    return;
                }
                String response = java_client.send(this.command + " " + this.input.getText());
                outputLine.setText("Send command : " + this.command + " " + this.input.getText());
                this.output.setText(response.replace("; ", "\n"));
            } catch (Exception ex) {
                outputLine.setText("Connecting Error");
            }
        }
    }

    // Listener for the quit menu entry
    private static class QuitListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }
}