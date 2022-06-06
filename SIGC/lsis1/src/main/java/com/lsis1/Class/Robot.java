package com.lsis1.Class;

public class Robot {
    private int id;
    private int idEquipa;
    private String nome;
    private String macAdress;

    private static int contador = 0;
    private static final int INT_DEFAULT = 0;
    private static final String STR_DEFAULT = "";

    public Robot(){
        this.id = ++contador;
        this.idEquipa = INT_DEFAULT;
        this.nome = STR_DEFAULT;
        this.macAdress = STR_DEFAULT;
    }

    public Robot(int idEquipa, String nome, String macAdress){
        this.id = ++contador;
        this.idEquipa = idEquipa;
        this.nome = nome;
        this.macAdress = macAdress;
    }

}