// Function to validate form input
function validateForm(form) {
    const quantity = form.querySelector('#quantity').value;
    const orderType = form.querySelector('#orderType').value;
    const price = form.querySelector('#price').value;

    if (quantity <= 0) {
        alert('Quantity must be greater than zero.');
        return false;
    }

    if (orderType === 'limit' && price.trim() === '') {
        alert('Please enter a limit price for a limit order.');
        return false;
    }

    return true;
}
