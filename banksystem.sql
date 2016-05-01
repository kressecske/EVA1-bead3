DROP DATABASE IF EXISTS banksystem;
CREATE DATABASE banksystem;
USE banksystem;

CREATE TABLE user(
    user_id VARCHAR(10) PRIMARY KEY,
    name VARCHAR(40) NOT NULL,
    password VARCHAR(40) NOT NULL,
    level INTEGER NOT NULL
);

CREATE TABLE client (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(30),
    address VARCHAR(30) NOT NULL,
    phone INTEGER
);

CREATE TABLE account(
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
    number INTEGER,
    create_date DATE,
    closed BOOLEAN,
    client_ID INTEGER,
    CONSTRAINT accounttoclient
		FOREIGN KEY(client_ID)
        REFERENCES client(id)
);

CREATE TABLE transaction(
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
    ammount INTEGER,
    from_account_ID INTEGER,
    to_account_id INTEGER,
    FOREIGN KEY(from_account_ID) REFERENCES account (id),
    FOREIGN KEY(to_account_ID) REFERENCES account(id)
);

insert into user(user_id, name, password, level) values('admin', 'Administrator','admin',0);
insert into user(user_id, name, password, level) values('test', 'Test','test',1);