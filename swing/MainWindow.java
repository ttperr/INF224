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
        this.setTitle("Multimedia Manager");

        // Set window default close operation
        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Add menu
        JMenu FileMenu = new JMenu("File");
        FileMenu.setMnemonic(KeyEvent.VK_F);
        
        JMenuItem QuitFileMenu = new JMenuItem("Quit");
        QuitFileMenu.setMnemonic(KeyEvent.VK_Q);
        QuitFileMenu.addActionListener(new QuitListener());
        
        FileMenu.add(QuitFileMenu);

        JMenuBar barMenu = new JMenuBar();
        barMenu.add(FileMenu);
        setJMenuBar(barMenu);

        JTextPane welcome = new JTextPane();
        welcome.setText("Welcome in the multimedia manager. " +
                "\nMultimedia objects available are : \n- photo.png \n- video.mp4" +
                "\nGroups available are : \n- group0");
        welcome.setEditable(false);

        JPanel outputPanel = new JPanel();
        outputLine = new JLabel("Disconnected");
        outputPanel.add(outputLine);

        JComponent mainMultimediaSection = multimediaSection("Multemedia object", "search", "play");
        JComponent mainGroupSection = groupSection("Groups", "search_group");
        
        JPanel sectionPanel = new JPanel();
        sectionPanel.setLayout(new GridLayout(1,2));
        sectionPanel.add(mainMultimediaSection);
        sectionPanel.add(mainGroupSection);

        add(welcome);
        add(sectionPanel);
        add(connection_section(mainMultimediaSection, mainGroupSection));
        add(outputPanel);

        pack();

        // Set window visibility
        this.setVisible(true);
        mainMultimediaSection.setVisible(false);
        mainGroupSection.setVisible(false);

    }

    // Connection section, containing inputs for IP address, port and a connection
    // button
    private JPanel connection_section(JComponent mainMultimediaSection, JComponent mainGroupSection) {
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
                        mainMultimediaSection.setVisible(false);
                        mainGroupSection.setVisible(false);
                    } else {
                        java_client = new JavaClient(ip_field.getText(), Integer.parseInt(port_field.getText()));
                        outputLine.setText("Connected");
                        connect_button.setText("STOP");
                        mainMultimediaSection.setVisible(true);
                        mainGroupSection.setVisible(true);
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
    private JComponent multimediaSection(String title, String searchCommand, String playCommand) {
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        
        JPanel toolsPanel = new JPanel();

        JTextField searchField = new JTextField(20);
        toolsPanel.add(searchField);

        JButton searchButton = new JButton("Search");
        searchButton.setBackground(Color.decode("#5cb85c"));
        searchButton.setForeground(Color.white);
        toolsPanel.add(searchButton);

        JButton playButton = new JButton("Play");
        playButton.setBackground(Color.decode("#0275d8"));
        playButton.setForeground(Color.white);
        toolsPanel.add(playButton);

        panel.add(toolsPanel);

        JTextArea textArea = new JTextArea(10, 40);
        textArea.setEditable(false);
        textArea.setBorder(BorderFactory.createLineBorder(Color.decode("#dddddd")));

        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        searchButton.addActionListener(new TcpCommand(searchCommand, searchField, textArea));
        playButton.addActionListener(new TcpCommand(playCommand, searchField, textArea));

        panel.add(scrollPane, BorderLayout.CENTER);
        return panel;
    }

    // Multimedia section, containing a search input, a search button
    // and a result textArea
    private JComponent groupSection(String title, String searchCommand) {
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder(title));
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    
        JPanel toolsPanel = new JPanel();
    
        JTextField searchField = new JTextField(20);
        toolsPanel.add(searchField);
    
        JButton searchButton = new JButton("Search");
        searchButton.setBackground(Color.decode("#5cb85c"));
        searchButton.setForeground(Color.white);
        toolsPanel.add(searchButton);
    
        panel.add(toolsPanel);
    
        JTextArea textArea = new JTextArea(10, 40);
        textArea.setEditable(false);
        textArea.setBorder(BorderFactory.createLineBorder(Color.decode("#dddddd")));
    
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
    
        searchButton.addActionListener(new TcpCommand(searchCommand, searchField, textArea));
    
        panel.add(scrollPane);
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