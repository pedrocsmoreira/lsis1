package com.lsis1.Model;

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

    public Robot(Robot r){
        this.id = r.id;
        this.idEquipa = r.idEquipa;
        this.nome = r.nome;
        this.macAdress = r.macAdress;
    }

    public int getID(){
        return this.id;
    }

    public void setIdEquipa(int idEquipa){
        this.idEquipa = idEquipa;
    }

    public int getIdEquipa(){
        return this.idEquipa;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public String getNome(){
        return this.nome;
    }

    public void setMacAdress(String macAdress){
        this.macAdress = macAdress;
    }

    public String getMacAdress(){
        return this.macAdress;
    }

}