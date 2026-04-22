window.onload = displayLinks;

function saveLetter() {
    const title = document.getElementById('title').value;
    const content = document.getElementById('content').value;

    if (!title || !content) return alert("Please fill in the title and text.");

    const newLetter = {
        id: Date.now(), // Unique ID for every "new" letter
        title: title,
        content: content,
        date: new Date().toLocaleDateString()
    };

    let archive = JSON.parse(localStorage.getItem('myArchive')) || [];
    archive.push(newLetter);
    localStorage.setItem('myArchive', JSON.stringify(archive));

    document.getElementById('title').value = '';
    document.getElementById('content').value = '';
    displayLinks();
}

function displayLinks() {
    const list = document.getElementById('letter-links');
    const archive = JSON.parse(localStorage.getItem('myArchive')) || [];

    // Creates the "Blue Link" list style
    list.innerHTML = archive.map((letter, index) => `
        <li>
            <a href="#" onclick="viewLetter(${letter.id})">${letter.title}</a> 
            <span class="date-tag">(${letter.date})</span>
            <button class="del-btn" onclick="deleteLetter(${index})">×</button>
        </li>
    `).join('');
}

function viewLetter(id) {
    const archive = JSON.parse(localStorage.getItem('myArchive'));
    const letter = archive.find(l => l.id === id);

    document.getElementById('view-title').innerText = letter.title;
    document.getElementById('view-date').innerText = "Date: " + letter.date;
    document.getElementById('view-content').innerText = letter.content;
    
    document.getElementById('viewer').classList.remove('hidden');
    document.getElementById('letter-links').classList.add('hidden');
}

function closeViewer() {
    document.getElementById('viewer').classList.add('hidden');
    document.getElementById('letter-links').classList.remove('hidden');
}

function deleteLetter(index) {
    let archive = JSON.parse(localStorage.getItem('myArchive'));
    archive.splice(index, 1);
    localStorage.setItem('myArchive', JSON.stringify(archive));
    displayLinks();
}