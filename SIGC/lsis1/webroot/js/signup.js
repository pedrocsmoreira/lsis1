function signup(){
    let form = document.getElementById("formSignUp");
    let formdata = new FormData(form);
    return fetch("/signup",{
        method: 'POST',
        body: formdata
    }).then((res) => {
        if (res.status === 200)
            return res.json();
        else
            window.alert("O username do utilizador inserido não existe!");
        throw Error("Erro no servidor!!");
        if(){
            document.getElementById("formSignUp").submit();
            window.location.assign("/criarComp");
        }
    }).then((result) => {
        console.log("LOGIN FEITO");
    }).catch(erro => {
        console.log(erro);
    });
}