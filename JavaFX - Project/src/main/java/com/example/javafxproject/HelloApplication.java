package com.example.javafxproject;

import com.example.javafxproject.domain.Friendship;
import com.example.javafxproject.domain.Message;
import com.example.javafxproject.domain.User;
import com.example.javafxproject.domain.validators.FriendshipValidator;
import com.example.javafxproject.domain.validators.MessageValidator;
import com.example.javafxproject.domain.validators.UserValidator;
import com.example.javafxproject.domain.validators.Validator;
import com.example.javafxproject.gui.Login;
import com.example.javafxproject.repository.db.DbFriendshipRepository;
import com.example.javafxproject.repository.db.DbMessageRepository;
import com.example.javafxproject.repository.db.DbUserRepository;
import com.example.javafxproject.service.FriendshipService;
import com.example.javafxproject.service.MessageService;
import com.example.javafxproject.service.UserService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        Validator<User> userValidator = new UserValidator();
        Validator<Friendship> friendshipValidator = new FriendshipValidator();
        Validator<Message> messageValidator = new MessageValidator();

        DbUserRepository userRepository = new DbUserRepository(userValidator,
                "jdbc:postgresql://localhost:5432/JavaFx","postgres","1234");
        DbFriendshipRepository friendshipRepository = new DbFriendshipRepository(friendshipValidator,
                "jdbc:postgresql://localhost:5432/JavaFx","postgres","1234");
        DbMessageRepository messageRepository = new DbMessageRepository(messageValidator,
                "jdbc:postgresql://localhost:5432/JavaFx","postgres","1234");

        UserService userService = new UserService(userRepository);
        FriendshipService friendshipService = new FriendshipService(friendshipRepository);
        MessageService messageService = new MessageService(messageRepository);

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("login.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
        stage.setTitle("Hello world!");
        Login login = fxmlLoader.getController();
        login.setService(userService, friendshipService, messageService);
        System.out.println("Service set");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}