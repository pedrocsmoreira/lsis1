function registoOrganizacao(){
    let form = document.getElementById("formRegistoOrganizacao");
    let formdata = new FormData(form);
    return fetch("/Organizacao/registoOrganizacao",{
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

function registoCompeticao(){
    let form = document.getElementById("formRegistoCompeticao");
    let formdata = new FormData(form);
    return fetch("/Competicao/registoCompeticao",{
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

function registoEquipa(){
    let form = document.getElementById("formRegistoEquipa");
    let formdata = new FormData(form);
    return fetch("/Equipa/registoEquipa",{
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

function registoJuri(){
    let form = document.getElementById("formRegistoJuri");
    let formdata = new FormData(form);
    return fetch("/Juri/registoJuri",{
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

