(if
 t  ;; to save on those precious indentations

 (progn
   (defun bounded? (location)
	 (every (lambda (x) (and (>= x 0) (< x 3))) location))

   (defun location-to-digit (location)
	 (1+ (+ (* (second location) 3) (first location))))

   (defun move-to-direction (move)
	 (case move
	   (#\U '(0 -1))
	   (#\D '(0 1))
	   (#\L '(-1 0))
	   (#\R '(1 0))))

   (let ((current-location '(1 1)) (final-digits '()))
	 (dolist (line (uiop:read-file-lines "../../inputs/2016/2"))
	   ;; (format t "~%~a~%" line)
	   ;; (format t "~%")
	   (loop :for move :across line :do
		 ;; (format t "~a " move)
		 (let* ((direction (move-to-direction move))
				(new-location (mapcar #'+ current-location direction)))
		   ;; (format t "~%")
		   ;; (format t "D: ~a -> ~a # " move direction)
		   ;; (format t "L: (~a + ~a) -> ~a -> ~a # " current-location direction new-location (location-to-digit new-location))
		   ;; (format t "#~a: (~a, ~a~a) = ~a~a" (length final-digits) move (location-to-digit current-location) current-location (location-to-digit new-location) new-location)
		   (if (bounded? new-location) (setq current-location new-location))))
	   ;; (format t "~%Digit: ~a" (location-to-digit current-location))
	   (setq final-digits (append final-digits (list (location-to-digit current-location)))))
	 (format t "~%~a is the code to unlock the door" final-digits))
   )

 (progn
   (let ((line (uiop:read-file-line "../../inputs/2016/2")))
	 (format t "~%~a: ~a" (length line) line)
	 (format t "~%Does it have newlines? ~a" (count #\Newline line)))
   (let ((lines (uiop:read-file-lines "../../inputs/2016/2")))
	 (format t "~%~a: ~a" (reduce #'+ (loop :for line :in lines :collect (length line))) lines))
   )

 )
	
