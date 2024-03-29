package com.example.javafxproject.gui;

import com.example.javafxproject.domain.User;
import com.example.javafxproject.domain.UserDTO;
import com.example.javafxproject.domain.validators.ArgumentException;
import com.example.javafxproject.service.FriendshipService;
import com.example.javafxproject.service.MessageService;
import com.example.javafxproject.service.UserService;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

public class MainWindow {
    ObservableList<UserDTO> modelUser = FXCollections.observableArrayList();

    @FXML
    private TextField searchBar;

    @FXML
    private Button buttonTrue;

    @FXML
    private Button buttonFalse;

    @FXML
    private TableColumn<UserDTO, String> columnFrom;

    @FXML
    private TableColumn<UserDTO, String> columnFirstname;

    @FXML
    private TableColumn<UserDTO, String> columnLastname;

    @FXML
    private TableColumn<UserDTO, String> columnMail;

    @FXML
    private TableView<UserDTO> mainTable;
    @FXML
    private Label welcomeText;

    private UserService userService;
    private FriendshipService friendshipService;
    private MessageService messageService;
    private User loggedUser;

    public void setUserService(UserService userService) {
        this.userService = userService;
    }

    public void setFriendshipService(FriendshipService friendshipService) {
        this.friendshipService = friendshipService;
    }

    public void setLoggedUser(User loggedUser) {
        this.loggedUser = loggedUser;
    }

    public void setAll(UserService userService, FriendshipService friendshipService, MessageService messageService) {
        setUserService(userService);
        setFriendshipService(friendshipService);
        setLoggedUser(loggedUser);
        this.messageService = messageService;
        welcomeText.setText("Welcome " + loggedUser.getFirstname());
    }

    private List<UserDTO> getFriendsDto(String status) {
        List<Long> idList = friendshipService.getRequests(loggedUser.getId(), status);

        return idList.stream().map(x -> userService.findOne(x)).toList()
                .stream()
                .map(x -> new UserDTO(x.getId(),x.getFirstname(), x.getLastname(), x.getEmail(),
                        friendshipService.getFriendsFrom(x.getId(), loggedUser.getId())))
                .collect(Collectors.toList());
    }

    private List<UserDTO> getUsersNotFriends() {
        List<Long> idList = friendshipService.getDiscover(loggedUser.getId(), userService.findAll().size());

        return idList.stream().map(x -> userService.findOne(x)).toList()
                .stream()
                .map(x -> new UserDTO(x.getId(),x.getFirstname(), x.getLastname(), x.getEmail()))
                .collect(Collectors.toList());
    }

    private List<UserDTO> getFriendRequestsSent() {
        List<Long> idList = friendshipService.getFriendRequestsSent(loggedUser.getId());

        return idList.stream().map(x -> userService.findOne(x)).toList()
                .stream()
                .map(x -> new UserDTO(x.getId(), x.getFirstname(), x.getLastname(), x.getEmail(),
                        friendshipService.getFriendsFrom(loggedUser.getId(), x.getId()))).collect(Collectors.toList());
    }


    @FXML
    private void initialize() {
        columnFirstname.setCellValueFactory(new PropertyValueFactory<>("firstname"));
        columnLastname.setCellValueFactory(new PropertyValueFactory<>("lastname"));
        columnMail.setCellValueFactory(new PropertyValueFactory<>("email"));
        columnFrom.setCellValueFactory(new PropertyValueFactory<>("friendsFrom"));

        mainTable.setItems(modelUser);
        buttonTrue.setText("Delete Friend");
        buttonFalse.setText("Open chat");
        disableButtons();
    }

    public void populateFriends() {
        modelUser.clear();
        columnFrom.setVisible(true);
        modelUser.setAll(getFriendsDto("accepted"));

        buttonTrue.setText("Delete Friend");

        buttonFalse.setVisible(true);
        buttonFalse.setText("Open chat");

        searchBar.setVisible(false);
        if (mainTable.getSelectionModel().isEmpty()) {
            disableButtons();
        }
    }

    public void populateRequests() {
        modelUser.clear();
        columnFrom.setVisible(true);
        modelUser.setAll(getFriendsDto("sent"));

        buttonFalse.setVisible(true);
        searchBar.setVisible(false);
        buttonTrue.setText("Accept");
        buttonFalse.setText("Decline");
        if (mainTable.getSelectionModel().isEmpty()) {
            disableButtons();
        }
    }

    public void populateDiscover() {
        modelUser.clear();
        columnFrom.setVisible(false);
        modelUser.setAll(getUsersNotFriends());

        searchBar.setVisible(true);
        buttonFalse.setVisible(false);
        buttonTrue.setText("Add new friend");

        if (mainTable.getSelectionModel().isEmpty()) {
            disableButtons();
        }
    }

    public void selectedItemFromTable() {
        buttonTrue.setDisable(false);
        buttonFalse.setDisable(false);
    }

    private void disableButtons() {
        buttonTrue.setDisable(true);
        buttonFalse.setDisable(true);
    }

    public void onTrueButtonPressed() {
        UserDTO wantUser = modelUser.get(mainTable.getSelectionModel().getFocusedIndex());
        if (buttonTrue.getText().equals("Accept")) {
            friendshipService.confirmFriends(wantUser.getId(), loggedUser.getId());
            populateRequests();
        } else if (buttonTrue.getText().equals("Add new friend")) {
            friendshipService.addFriend(loggedUser.getId(), wantUser.getId());
            populateDiscover();
        } else if (buttonTrue.getText().equals("Delete")) {
            friendshipService.removeFriend(loggedUser.getId(), wantUser.getId());
            populateSentReq();
        } else {
            try {
                friendshipService.removeFriend(loggedUser.getId(), wantUser.getId());
                friendshipService.removeFriend(wantUser.getId(), loggedUser.getId());
            } catch(ArgumentException ignored){}
            populateFriends();
        }
    }

    public void onFalseButtonPressed() throws IOException {
        if (buttonFalse.getText().equals("Decline")) {
            UserDTO wantUser = modelUser.get(mainTable.getSelectionModel().getFocusedIndex());
            friendshipService.removeFriend(wantUser.getId(), loggedUser.getId());
            populateRequests();
        } else if (buttonFalse.getText().equals("Open chat")) {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/com/example/javafxproject/chat.fxml"));
            AnchorPane pane = fxmlLoader.load();
            UserDTO user = mainTable.getSelectionModel().getSelectedItem();
            Chat chat = fxmlLoader.getController();

            chat.setRepo(messageService, userService);
            chat.setUsers(loggedUser, userService.findOne(user.getId()));

            Stage stage = new Stage();
            stage.setScene(new Scene(pane));

            stage.setTitle("Conversation with: " + user.getFirstname());

            stage.show();

        }
    }

    public void logOut() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/com/example/javafxproject/login.fxml"));
        VBox vBox = fxmlLoader.load();
        Login login = fxmlLoader.getController();
        login.setService(userService, friendshipService, messageService);
        login.setInitMsg("Successfully logged out");

        Stage stage = new Stage();
        stage.setScene(new Scene(vBox));

        stage.setTitle("Login");
        stage.show();

        closeWindow();
    }

    private void closeWindow() {
        Stage thisStage = (Stage) mainTable.getScene().getWindow();
        thisStage.close();
    }

    public void populateSentReq() {
        modelUser.clear();
        columnFrom.setVisible(true);
        modelUser.setAll(getFriendRequestsSent());

        buttonFalse.setVisible(false);
        searchBar.setVisible(false);
        buttonTrue.setText("Delete");
        if (mainTable.getSelectionModel().isEmpty()) {
            disableButtons();
        }
    }
}
