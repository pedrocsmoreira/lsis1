package com.lsis1;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBConnection {
    private static final String database = 'jdbc:mysql://localhost:3036/' + '';
	private static final String user = 'test';
	private static final String pass = 'test';

	public static Connection getConnection(){
		try{
			Connection conn = DriverManager.getConnection(database, user, pass);
			System.out.println(String.format("Connection to %s "+ "succeded!", conn.getCatalog())); return conn ;
		}catch(SQLException exc) {
			throw new RuntimeException("!!!!Error connecting!!!!", exc);
		}
	}
}