CREATE TABLE pfh4_User(
   ID_user SMALLINT,
   fee SMALLINT,
   name VARCHAR(50),
   surname VARCHAR(50),
   email VARCHAR(255) NOT NULL,
   phone_number integer NOT NULL,
   password VARCHAR(50),
   Address VARCHAR(255),
   Admin boolean,
   nickname VARCHAR(50),
   IP inet,
   PRIMARY KEY(ID_user)
);

CREATE TABLE Package(
   ID_app SMALLINT,
   fee_min timestamp,
   Prices SMALLINT,
   PRIMARY KEY(ID_app)
);

CREATE TABLE Scooter(
   ID_scooter SMALLINT,
   usage_history INT,
   battery integer,
   used boolean,
   _Timestamp timestamp,
   geolocation INT,
   ID_app SMALLINT NOT NULL,
   PRIMARY KEY(ID_scooter),
   FOREIGN KEY(ID_app) REFERENCES Package(ID_app)
);

CREATE TABLE pfh4_Accessories(
   ID_accounts INT,
   Products VARCHAR(150),
   Quantity SMALLINT,
   Price SMALLINT NOT NULL,
   PRIMARY KEY(ID_accounts)
);

CREATE TABLE Benefit(
   ID_Service_Provider SMALLINT,
   enterprise_name VARCHAR(100),
   repair VARCHAR(255),
   price SMALLINT,
   PRIMARY KEY(ID_Service_Provider)
);

CREATE TABLE Weather_Report(
   ID_geolocation VARCHAR(50),
   Date_Time timestamp,
   Temp float8,
   Feels_like float8,
   Temp_min float8,
   Temp_max float8,
   Pressure int2,
   Sea_lvl int2,
   Grnd_lvl int2,
   Humidity int2,
   Temp_kf float8,
   Main_cast VARCHAR(50),
   Description VARCHAR(50),
   Wind_speed float8,
   Wind_deg float8,
   Wind_gust float8,
   Visibility integer,
   Sunrise_time integer,
   Sunset_time integer,
   PRIMARY KEY(ID_geolocation)
);

CREATE TABLE pfh4_Account(
   ID_account SMALLINT,
   quantity_points_fidelity SMALLINT,
   user_password VARCHAR(255) NOT NULL,
   user_email VARCHAR(50) NOT NULL,
   user_nickname VARCHAR(50) NOT NULL,
   ID_geolocation VARCHAR(50) NOT NULL,
   ID_app SMALLINT,
   ID_user SMALLINT NOT NULL,
   PRIMARY KEY(ID_account),
   UNIQUE(ID_user),
   FOREIGN KEY(ID_geolocation) REFERENCES Weather_Report(ID_geolocation),
   FOREIGN KEY(ID_app) REFERENCES Package(ID_app),
   FOREIGN KEY(ID_user) REFERENCES pfh4_User(ID_user)
);

CREATE TABLE Fidelity_points(
   ID_order SMALLINT,
   Quantity SMALLINT,
   purchase_history DATE,
   Discount SMALLINT,
   ID_account SMALLINT NOT NULL,
   PRIMARY KEY(ID_order),
   FOREIGN KEY(ID_account) REFERENCES pfh4_Account(ID_account)
);

CREATE TABLE pfh4_Bills(
   ID_bill SMALLINT,
   purchase_historic DATE,
   content VARCHAR(255),
   quantity SMALLINT,
   gained_points SMALLINT,
   ID_order SMALLINT NOT NULL,
   ID_account SMALLINT NOT NULL,
   PRIMARY KEY(ID_bill),
   FOREIGN KEY(ID_order) REFERENCES Fidelity_points(ID_order),
   FOREIGN KEY(ID_account) REFERENCES pfh4_Account(ID_account)
);

CREATE TABLE Service(
   ID_scooter SMALLINT,
   ID_Service_Provider SMALLINT,
   PRIMARY KEY(ID_scooter, ID_Service_Provider),
   FOREIGN KEY(ID_scooter) REFERENCES Scooter(ID_scooter),
   FOREIGN KEY(ID_Service_Provider) REFERENCES Benefit(ID_Service_Provider)
);

CREATE TABLE buy(
   ID_accounts INT,
   ID_account SMALLINT,
   PRIMARY KEY(ID_accounts, ID_account),
   FOREIGN KEY(ID_accounts) REFERENCES pfh4_Accessories(ID_accounts),
   FOREIGN KEY(ID_account) REFERENCES pfh4_Account(ID_account)
);

CREATE TABLE points(
   ID_accounts INT,
   ID_order SMALLINT,
   PRIMARY KEY(ID_accounts, ID_order),
   FOREIGN KEY(ID_accounts) REFERENCES pfh4_Accessories(ID_accounts),
   FOREIGN KEY(ID_order) REFERENCES Fidelity_points(ID_order)
);
