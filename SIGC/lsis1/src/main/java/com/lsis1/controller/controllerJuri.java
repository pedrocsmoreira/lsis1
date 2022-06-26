package com.lsis1.controller;

import com.lsis1.database.DBConnection;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class controllerJuri {
    




    
    public int deleteJuri(int id_competicao, int id_juri) throws SQLException {
        String SQL = "DELETE FROM associar_juri WHERE id_juri = ? AND id_competicao = ?";
        int res = 0;
        Connection conn = DBConnection.getConnection();
        PreparedStatement ps;

        try{
            ps = conn.prepareStatement(SQL);
            ps.setInt(1,id_juri);
            ps.setInt(2,id_competicao);
            res = ps.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
 
        conn.close();
        return res; 
    } 
}
