function login(){
    let form = document.getElementById("formLogin");
    let formdata = new FormData(form);
    return fetch("/login",{
        method: 'POST',
        body: formdata
    }).then((res) => {
        if (res.status === 200)
            return res.json();
        else
            window.alert("O username do utilizador inserido não existe!");
        throw Error("Erro no servidor!!");
    }).then((result) => {
        console.log("LOGIN FEITO");
    }).catch(erro => {
        console.log(erro);
    });
}