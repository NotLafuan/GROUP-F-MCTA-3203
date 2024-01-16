function pad(num, size) {
    num = num.toString();
    while (num.length < size) num = "0" + num;
    return num;
}

async function updateStatus() {
    const spans = document.querySelectorAll('span');
    while (true) {
        try {
            spans.forEach(async span => {
                console.error(span.id);
                if (span.id == "status") {
                    const response = await fetch('/get_status');
                    const data = await response.text();
                    if (data == 0) {
                        span.textContent = "Stopped";
                        span.classList.remove('gray');
                        span.classList.remove('green');
                        span.classList.add('red');
                    } else if (data == 1) {
                        span.textContent = "Running";
                        span.classList.remove('gray');
                        span.classList.add('green');
                        span.classList.remove('red');
                    } else if (data == 2) {
                        span.textContent = "Paused";
                        span.classList.add('gray');
                        span.classList.remove('green');
                        span.classList.remove('red');
                    }
                } else if (span.id == "timer") {
                    const response = await fetch('/get_timer');
                    const data = await response.text();
                    const timer = parseInt(data);
                    const minutes = Math.floor(timer / 60)
                    const seconds = timer % 60
                    span.textContent = minutes.toString() + ":" + pad(seconds, 2);
                } else if (span.id == "mode") {
                    const response = await fetch('/get_mode');
                    const data = await response.text();
                    span.textContent = data;
                }
            })
            await new Promise(resolve => setTimeout(resolve, 500));
        } catch (error) {
            console.error('An error occurred:', error);
        }
    }
}

updateStatus();