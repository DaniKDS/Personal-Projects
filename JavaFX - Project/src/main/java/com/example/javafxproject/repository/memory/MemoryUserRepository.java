package com.example.javafxproject.repository.memory;

import com.example.javafxproject.domain.User;
import com.example.javafxproject.domain.validators.Validator;

/**
 * Implements the given interface
 */
public class MemoryUserRepository extends MemoryRepository<Long, User> {
    public MemoryUserRepository(Validator<User> validator) {
        super(validator);
    }

    public Long getLowestFreeId() {
        for (Long i = 1L; ; ++i) {
            if (!entities.containsKey(i)) {
                return i;
            }
        }
    }
}
