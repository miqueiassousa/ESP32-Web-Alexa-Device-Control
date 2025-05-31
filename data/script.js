function led1() {
  fetch('/led1')
    .then(response => response.text())
    .then(data => console.log(data));
}

function led2() {
  fetch('/led2')
    .then(response => response.text())
    .then(data => console.log(data));
}

function led3() {
  fetch('/led3')
    .then(response => response.text())
    .then(data => console.log(data));
}

function desligar_tudo() {
  fetch('/desligar_tudo')
    .then(response => response.text())
    .then(data => console.log(data));
}
