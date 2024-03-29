package com.example.javafxproject.gui;

import com.example.javafxproject.domain.Message;
import com.example.javafxproject.domain.MessageDTO;
import com.example.javafxproject.domain.User;
import com.example.javafxproject.service.MessageService;
import com.example.javafxproject.service.UserService;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDateTime;
import java.util.List;

public class Chat {
    ObservableList<MessageDTO> messageDTOS = FXCollections.observableArrayList();

    private MessageService messageService;
    private UserService userService;

    private User sender;
    private User receiver;

    @FXML
    private TableView<MessageDTO> tableView;

    @FXML
    private TableColumn<MessageDTO, String> messageColumn;

    @FXML
    private TextField messageField;

    @FXML
    public void initialize() {
        messageColumn.setCellValueFactory(new PropertyValueFactory<>("message"));

        tableView.setItems(messageDTOS);
    }

    private String getStringForDTO(Message message) {
        String prefix;
        if (message.getIdFrom().equals(sender.getId())) {
            prefix = "Me: ";
        } else {
            prefix = receiver.getFirstname() + ": ";
        }
        return prefix + message.getMessage();
    }

    public List<MessageDTO> getMessageDTO() {
        List<Message> messages = messageService.getMessages(sender.getId(), receiver.getId());

        return messages.stream()
                .map(x -> new MessageDTO(x.getId(), getStringForDTO(x), x.getSendTime())).toList();
    }

    public void setRepo(MessageService msgRepo, UserService userRepo) {
        messageService = msgRepo;
        userService = userRepo;
    }

    public void setUsers(User tmpSender, User tmpReceiver) {
        sender = tmpSender;
        receiver = tmpReceiver;
        messageDTOS.setAll(getMessageDTO());
    }

    public MessageService getMessageService() {
        return messageService;
    }

    public void setMessageService(MessageService messageService) {
        this.messageService = messageService;
    }

    public UserService getUserService() {
        return userService;
    }

    public void setUserService(UserService userService) {
        this.userService = userService;
    }

    public void sendClicked() {
        if (messageField.getText().equals("")) {
            return;
        }

        messageService.add(messageField.getText(), sender.getId(), receiver.getId(), LocalDateTime.now());
        messageDTOS.setAll(getMessageDTO());
        messageField.clear();
    }
}
