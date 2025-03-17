(ql:quickload "cl-ppcre")

(progn

  (defun shift-cipher (c by)
	(code-char (+ (mod (+ (- (char-code c) (char-code #\a)) by) 26)
				  (char-code #\a))))

  (defun shift-cipher-string (str by)
	(map 'string (lambda (c) (if (eql c #\-) #\Space (shift-cipher c by))) str))

  (let ((sum-part1 0) (section-id-part2 nil))
	(dolist (room (uiop:read-file-lines "../../inputs/2016/4"))
	  ;; (format t "~%~a" room)
	  (ppcre:register-groups-bind (name section-id-str checksum) ("^([\\w-]+)-(\\d+)\\[(\\w+)\\]$" room)
		(let ((name-clear (remove #\- name)) (section-id (parse-integer section-id-str))
			  (forward-alist '()) (reverse-alist '()))

		  (format t "~%~%name: ~a" name)
		  (format t "~%name-clear: ~a" name-clear)
		  
		  (loop :for letter :across name-clear :do
			(let ((cell (assoc letter forward-alist)))
			  (if cell
				  (incf (cdr cell))
				  (push (cons letter 1) forward-alist))))
		  (format t "~%forward-alist: ~a" forward-alist)

		  (loop :for cell :in forward-alist :do
			(let* ((letter (car cell)) (count (cdr cell))
				   (rcell (assoc count reverse-alist)))
			  (if rcell
				  (push letter (cdr rcell))
				  (push (cons count (list letter)) reverse-alist))))
		  (format t "~%reverse-alist: ~a ~a" (length reverse-alist) reverse-alist)

		  (setq reverse-alist (sort reverse-alist #'> :key #'car))
		  (format t "~%partially sorted reverse-alist: ~a ~a" (length reverse-alist) reverse-alist)

		  (dolist (cell reverse-alist)
			(setf (cdr cell) (sort (cdr cell) #'char-lessp)))
		  (format t "~%sorted reverse-alist: ~a ~a" (length reverse-alist) reverse-alist)

		  (let ((real-checksum (subseq
								(reduce (lambda (a b) (concatenate 'string a b))
										(mapcar (lambda (cell) (coerce (cdr cell) 'string)) reverse-alist))
								0 5)))
			(format t "~%real-checksum: ~a" real-checksum)
			(if (equal real-checksum checksum)
				(incf sum-part1 section-id)))
		  (format t "~%given checksum: ~a" checksum)

		  (format t "~%section-id: ~a" section-id)

		  (let ((decrypted-name (shift-cipher-string name section-id)))
			(if (ppcre:scan "north\\s*pole\\s*object" decrypted-name)
				(setq section-id-part2 section-id))
			(print decrypted-name))
		  )))

	(format t "~%~%Sum of section IDs of only the real rooms is ~a" sum-part1)
	(format t "~%Section of room where North Pole objects are kept is ~a" section-id-part2)
	)
  )

