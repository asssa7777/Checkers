# Checkers
Game "Checkers" in Java &amp; C++
Project Overview:
Developed a two-player board game application utilizing Java and C++ through the Java Native Interface (JNI). The project involved creating an interactive GUI that operates without storing game state on the Java side, ensuring that all game logic and state management reside entirely within the C++ module. The interface facilitates game moves via both mouse and keyboard, designed to deliver a seamless user experience and responsive gameplay.

Technologies & Skills:

 • Java & C++ Integration (JNI): Established robust communication between Java and C++ to ensure real-time data retrieval from the C++ game logic, allowing Java to access game state without local storage on the Java module side.
 • Graphical User Interface (Java Swing/JavaFX): Designed and implemented a responsive and interactive GUI, featuring board and piece displays, enabling player moves through both mouse and keyboard controls.
 • Game Logic & State Management (C++): Programmed all game mechanics, including board initialization, piece movements, and capture mechanisms, in C++ to centralize and secure game rules and state data.
 • Unit Testing (JUnit 5): Developed a comprehensive suite of unit tests to validate game functionality:
 • Board initialization and readiness verification.
 • Move validation tests, ensuring all player actions comply with game rules.
 • Capture functionality tests, confirming opponent pieces are handled correctly.

Key Accomplishments:

 • Delivered an efficient, cross-language board game that leverages JNI to maintain a clear separation of GUI and game logic.
 • Implemented modular, testable code, ensuring the integrity of game rules and performance across different environments.
 • Created an interactive and user-friendly interface that enhances the gaming experience and supports both keyboard and mouse controls.
