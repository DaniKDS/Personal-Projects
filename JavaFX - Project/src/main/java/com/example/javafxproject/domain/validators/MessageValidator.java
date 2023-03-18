package com.example.javafxproject.domain.validators;

import com.example.javafxproject.domain.Message;

public class MessageValidator implements  Validator<Message> {

    @Override
    public void validate(Message entity) throws ValidationException {
        String err = "";

        if (entity.getMessage().equals("")) {
            err += "The message cannot be void";
        }

        if (!err.equals("")) {
            throw new ValidationException(err);
        }
    }
}
