function login(){
    console.log("ENTROU NO LOGIN");
    return fetch("/login").then((res) => {
        return res.json();
    }).then((result) => {
        console.log("LOGIN FEITO");
    }).catch(erro => {
        console.log(erro);
    });
}