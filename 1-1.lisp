(if t

	;; real deal brother
	(progn

	  (with-open-file (stream "inputs/1")
		)

	  )

	;; experimentation and learning
	(progn

	  (with-open-file (stream "/dev/shm/test.txt" :direction :input :element-type 'character)
		;; 0
		(dolist (item (list '(file-position lstream) '(probe-file lstream) '(directory lstream) '(file-write-date lstream)
							'(truename lstream) '(read-line lstream nil) '(file-author "/") '(file-length lstream)
							'(file-position lstream)))
		  (defparameter lstream stream)
		  (format t "~%~a = ~a " item (eval item)))

		;; 1
		(file-position stream 0)
		(let ((input (make-string (file-length stream) :initial-element #\~)))
		  (print "=================")
		  (read-sequence input stream)
		  input)
		
		)

	  ))

