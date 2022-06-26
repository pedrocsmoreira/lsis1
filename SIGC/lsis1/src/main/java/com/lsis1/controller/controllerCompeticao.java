package com.lsis1.controller;

public class controllerCompeticao {
    




    public ArrayList<Competicao> getCompeticoesJuri() throws SQLException {
        String GET_SQL = "SELECT * FROM Competicao";
        String ASSOCIACAO_SQL = "SELECT * FROM associar_juri WHERE id_juri = ? AND id_competicao = ?;";

        boolean res = true;
        ArrayList<Competicao> listaCompeticoes = new ArrayList<>();
        Connection conn = DBConnection.getConnection();
        PreparedStatement ps;
        ResultSet rset = null;
        try {
            ps = conn.prepareStatement(GET_SQL);
            rset = ps.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        while (res) {
            assert rset != null;
            if (rset.next()) {
                Competicao comp = new Competicao();
                comp.setId(rset.getInt("id"));
                comp.setId_organizador(rset.getInt("id_organizador"));
                comp.setNome(rset.getString("nome"));
                comp.setDesc(rset.getString("descricao"));
                comp.setNrondas(rset.getInt("nrondas"));
                comp.setMax_equipas(rset.getInt("max_equipas"));
                listaCompeticoes.add(comp);
            } else {
                res = false;
            }
        }

        for (int i = 0; i < listaCompeticoes.size(); i++) {
            ps = conn.prepareStatement(ASSOCIACAO_SQL);
            LoginHandler lh = new LoginHandler();
            ps.setInt(1, lh.getUser().getId());
            ps.setInt(2, listaCompeticoes.get(i).getId());
            rset = ps.executeQuery();
            if (rset.next()) {
                listaCompeticoes.get(i).setJurilogadoAssociado(true);
            } else {
                listaCompeticoes.get(i).setJurilogadoAssociado(false);
            }
        }
        conn.close();
        System.out.println(listaCompeticoes);
        return listaCompeticoes;
    }
}
